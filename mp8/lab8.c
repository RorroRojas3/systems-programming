/* lab8.c
 * Rodrigo Ignacio Rojas Garcia
 * rrojas
 * ECE 2220, Fall 2016
 * MP8
 *
 * Purpose: The purpose of this program is to create a chat between two terminals by using the curses library.
 *
 * Assumptions: The port number MYPORT is assumed to be free.  If you
 *              get a failed to bind message try changing the port number
 *              to a larger value (but just increase by +1 until you find
 *              an open port)
 *
 *              To connect to a remote chat program, the port number use by
 *              both programs must be the same.
 *
 * Command line arguments: The hostname to chat with.
 *
 * Known bugs: Need to implement curses code.  What about really long lines?
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/wait.h>
#include <curses.h>

#define MYPORT "4950"  // the port users will be connecting to

#define MAXtextLEN 100

const char *welcome = "Welcome to ECE 222 chat";


// Collect input from keyboard and send packet to remote host
//
// input: sockfd  -- a socket has already been set up to the remote host
//
// output:
//    print input from keyboard to bottom half of screen
//
//    return a flag to indicate the program should quit
//         1 -- user typed "quit" so tell main to end
//         0 -- default: do not quit
//
int chat_talker(int sockfd, char **terminal_screen)
{
    // Variable Declaration Section
    static char text[MAXtextLEN];
    int numbytes;
    static int i = 0;
    int ch;
    char *temporary;
    int c1;
    int quit_flag = 0;
    int screen_middle = LINES/2;

    // Reads the input of the keyboard character by character
    if((ch = getch()) != '\n' && i != COLS - 1)
    {
        // Checks if the user backpasce character
        if (ch == KEY_BACKSPACE)
        {
          clrtoeol();
          if (i != 0)
          {
          	i--;
          }
          refresh();
        }
        else
        {
        	text[i++] = ch;
        }
    }

    else
    {
    	// Sets the NULL at the end of character variable text
   	 	text[i] = '\0';

    	// Allocated dynamic memory for temporary character variable.
    	temporary = (char *)calloc(strlen(text) + 1, sizeof(char));
    	strcpy(temporary, text);

      // If string is quit, it quits the program
    	if (strcmp(text, "quit") == 0)
			{
        quit_flag = 1;
    	}

    	if ((numbytes = send(sockfd, text, strlen(text), 0)) == -1)
			{
        perror("chat: send");
        exit(1);
    	}

    	// Sets the cursor of terminal to position of middle of screen of terminal + 1 and swaps the strings from the next LINES into current LINES
    	for (c1 = screen_middle + 1; c1 < LINES - 1; c1++)
   	 	{
				terminal_screen[c1]= terminal_screen[c1 + 1];
    	}

    	// Sets the word stored in temporary to terminal cursos LINES-2 which is one line before the entered word was entered.
    	terminal_screen[LINES-2] = temporary;

    	// Sets the terminal cursor to the location of middle of terminal screen -1 and moves the cursor each time and display a string
  		for (c1 = screen_middle + 1; c1 < LINES -1; c1++)
   		{
   			move(c1,0);
    		addstr(terminal_screen[c1]);
    		clrtoeol();
	 		}

    	// Move Cursor to Lower Left
    	move(LINES-1, 0);
    	// Clear current line to end of line
    	clrtoeol();
    	// Update Display
    	refresh();
      // Sets all character in text to NULL after function is ran
    	for (c1 = 0; c1 < strlen(text + 1); c1++)
    	{
    		text[c1] = '\0';
    	}
    	i = 0;
    }

    // Returns eiterh a 0 or a 1
    return quit_flag;
}

// Receive packets from a remote host.
//
// input: sockfd  -- a socket has already been set up to the remote host
//
// output: should print received data to top half of the screen
//
void chat_listener(int sockfd, char **terminal_screen)
{
    // Variable Declaration Section
    char text[MAXtextLEN];
    int numbytes;
    int screen_middle = LINES/2;
    int c1;
    char *temporary;
    int x;
    int y;

    // Gets the position of Terminal cursor
		getyx(stdscr,y,x);

    if ((numbytes = recv(sockfd, text, MAXtextLEN-1 , 0)) == -1)
    {
        perror("chat: recv");
        exit(1);
    }

    // Sets the NULL in text
    text[numbytes] = '\0';

    // Allocated dynamic memory for temporary character variable.
    temporary = (char *)calloc(strlen(text) + 1, sizeof(char));
    strcpy(temporary, text);

    // Sets the cursor of terminal to position 0 and swaps the strings from the next LINES into current LINES
    for (c1 = 0; c1 < screen_middle - 1; c1++)
    {
      terminal_screen[c1] = terminal_screen[c1 + 1];
    }

    // Sets the word stored in temporary to terminal cursor screen_middle -1 which is one line before the middle screen text
    terminal_screen[screen_middle - 1] = temporary;

    // Sets the terminal cursor to location 0 and moves the cursor eahc time and displays a string.
    for (c1 = 0; c1 < screen_middle; c1++)
    {
      move(c1,0);
      addstr(terminal_screen[c1]);
      clrtoeol();
    }

    // Move Cursor to Lower Left
    move(y,x);
    // Clear current line to end of line
    clrtoeol();
    refresh();
}

/* main sets up the structures with IP address information and calls
 * socket, bind, and connect to set up the details of the UDP socket.
 *
 * Use the select() function to wait for input from either the keyboard
 * or from the remote host
 *
 * Changes to main should be minimal.  Just initialize curses
 * and clean up at end.  All other work is in the two
 *    chat_talker
 *    chat_listener
 * functions that collect input that needs to be displayed
 */
int main(int argc, char *argv[])
{
    // Variable Declaration Section
    int sockfd;
    struct addrinfo hints, *addr_result, *p;
    int rv;
    char **terminal_screen;
    int c1;
    int screen_middle;
    char *screen_divider, *addr;

    if (argc != 2) {
        fprintf(stderr, "usage: chat hostname\n");
        exit(1);
    }

    // set up details for address information data structure
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    // first: open socket and bind to port on my host so
    // we can receive packets on this port

    // This fills in structure with IP details for the local host
    if ((rv = getaddrinfo(NULL, MYPORT, &hints, &addr_result)) != 0) {
        fprintf(stderr, "getaddrinfo my host: %s\n", gai_strerror(rv));
        return 1;
    }
    // loop through all the results and bind to the first we can
    for(p = addr_result; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                        p->ai_protocol)) == -1) {
            perror("chat: socket");
            continue;
        }
        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("chat: bind");
            continue;
        }
        break;
    }
    if (p == NULL) {
        fprintf(stderr, "chat: failed to bind to socket\n");
        return 2;
    }
    freeaddrinfo(addr_result);

    // second: repeat with remote host IP details so we can
    // connect this socket to the remote host only.  As an extension
    // you could use a different port number for the remote host.
    if ((rv = getaddrinfo(argv[1], MYPORT, &hints, &addr_result)) != 0) {
        fprintf(stderr, "getaddrinfo remote host: %s\n", gai_strerror(rv));
        return 1;
    }
    // loop through all the results and connect to the first we can
    for(p = addr_result; p != NULL; p = p->ai_next) {
        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("chat: connect");
            continue;
        }
        break;
    }
    if (p == NULL) {
        fprintf(stderr, "chat: failed to connect socket\n");
        return 2;
    }
    freeaddrinfo(addr_result);

    // End of code to set up UDP socket

    fprintf(stderr, "chat: waiting to chat with %s\n", argv[1]);

    // set up master set of file descriptors to use with select
    fd_set master;
    fd_set read_fds;

    FD_ZERO(&master);
    FD_ZERO(&read_fds);
    FD_SET(0, &master);   // standard input is zero
    FD_SET(sockfd, &master);

    initscr();
    keypad(stdscr, TRUE);

    // Allocated dynamic memory for screen_divider by making as big as the number of COLS + 1 of terminal.
    screen_divider = (char *) malloc((COLS+1) * sizeof(char));

    // Stores the location of middle of terminal in integer variable screen_middle by diving LINES by 2
    screen_middle = LINES/2;

    // Dynamic allocted character variable screen_divider is set to all empty spaces
    memset(screen_divider, ' ', COLS);

    // If the terminal has less than five columns, it will display that the screen is too small
    if (COLS < 5)
    {
    	fprintf(stderr, "Screen is too small %d\n", COLS);
    }

    // If the screen is not big enough it will only display "chat" in the middle of the screen
    else if (COLS < strlen(welcome) + strlen(argv[1]) + 1)
    {
      sprintf(screen_divider, "chat");
    }

    // Sets dynamic allocated character variable screen_divider to defined string welcome and sets character pointer addrs to defined string remote_name
    else
    {
        memcpy(screen_divider, welcome, strlen(welcome));
        addr = screen_divider + COLS - strlen(argv[1]);
        memcpy(addr, argv[1], strlen(argv[1]));
    }

    // Sets the NULL into dynamic allocated character variable screen_divider
    screen_divider[COLS] = '\0';

    // Moves the cursor of the terminal to it's middle, line screen_middle and column 0
    move(screen_middle, 0);
    // Makes the next string that will be printer bold
    standout();
    // Prints string screen_divider
    addstr(screen_divider);
    // Turns off set bold
    standend();
    // Moves the cursor of terminal to the lower left of the terminal
    move(LINES-1, 0);
    refresh();


    // Allocated dynamic memory for terminal_screen which makes it as big as the termial screen when opened.
    terminal_screen = (char **)calloc(LINES, sizeof(char *));
    for (c1 = 0; c1 < LINES; c1++)
    {
      terminal_screen[c1] = NULL;
    }

    int quit_flag = 0;    // changed by chat_talker when user types quit
    while(quit_flag == 0) {
        // specify who to monitor on this trial.  We want both
        read_fds = master;
        // block and wait for input from stdin or socket
        if (select(sockfd+1, &read_fds, NULL, NULL, NULL) == -1) {
            perror("chat: select");
            exit(4);
        }

        // which one is set?  Rare, but both could be set
        if (FD_ISSET(0, &read_fds)) {
            quit_flag = chat_talker(sockfd, terminal_screen);      // keyboard input
        }
        if (FD_ISSET(sockfd, &read_fds)) {
            chat_listener(sockfd, terminal_screen);                // remote host sent data
        }
    }

    // Closes socket
    close(sockfd);
    // Closes the curses commands
    endwin();
    // Frees dynamic allocated memory
    for (c1 = 0; c1 < LINES; c1++)
    {
      free(terminal_screen[c1]);
    }
    free(terminal_screen);
    free(screen_divider);

    return 0;
}
