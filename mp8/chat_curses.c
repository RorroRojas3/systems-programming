#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curses.h>

#define MAXtextLEN 80

const char *welcome = "Welcome to ECE 222 chat";
const char *remote_name = "apolloXX";

int main(void)
{
    // Variable Declaration Section
    char text[MAXtextLEN];
    int i;
    int screen_middle;
    char *screen_divider, *addr;
    int not_done = 1;
    int ch;
    char *temporary;
    char **terminal_screen;
    int c1;

    // Initialize Curses System.  Must be called first to set
    initscr();

    // Allocated dynamic memory for screen_divider by making as big as the number of COLS + 1 of terminal.
    screen_divider = (char *) malloc((COLS+1) * sizeof(char));

    // Allocated dynamic memory for terminal_screen which makes it as big as the termial screen when opened.
    terminal_screen = (char **)calloc(LINES, sizeof(char *));
    for (c1 = 0; c1 < LINES; c1++)
    {
      terminal_screen[c1] = (char *)calloc(COLS, sizeof(char));
    }

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
    else if (COLS < strlen(welcome) + strlen(remote_name) + 1)
    {
      sprintf(screen_divider, "chat");
    }

    // Sets dynamic allocated character variable screen_divider to defined string welcome and sets character pointer addrs to defined string remote_name
    else
    {
        memcpy(screen_divider, welcome, strlen(welcome));
        addr = screen_divider + COLS - strlen(remote_name);
        memcpy(addr, remote_name, strlen(remote_name));
    }

    // Sets the NULL into dynamic allocated character variable screen_divider
    screen_divider[COLS] = '\0';

    // Clears the terminal screen
    clear();
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

    while(not_done)
    {
        i = 0;
        // Reads the input of the keyboard character by character
        while((ch = getch()) != '\n')
        {
            text[i++] = ch;
        }
        // Sets the NULL at the end of character variable text
        text[i] = '\0';

        // Allocated dynamic memory for temporary character variable.
        temporary = (char *)calloc(strlen(text + 1), sizeof(char));
        strcpy(temporary, text);

        // If user enters "quit" the loop will exit and program will be terminated.
        if (strcmp(text, "quit") == 0)
        {
          not_done = 0;
        }

        // Sets the cursor of terminal to position of middle of screen of terminal + 1 and swaps the strings from the next LINES into current LINES
        for (c1 = screen_middle + 1; c1 < LINES -1; c1++)
        {
          terminal_screen[c1] = terminal_screen[c1 + 1];
        }

        // Sets the cursor of terminal to position 0 and swaps the strings from the next LINES into current LINES
        for (c1 = 0; c1 < screen_middle; c1++)
        {
          terminal_screen[c1] = terminal_screen[c1 + 1];
        }

        // Sets the word stored in temporary to terminal cursos LINES-2 which is one line before the entered word was entered.
        terminal_screen[LINES-2] = temporary;

        // Sets the word stored in temporary to terminal cursor screen_middle -1 which is one line before the middle screen text
        terminal_screen[screen_middle - 1] = temporary;

        // Clear the Screen
        clear();
        // Moves the cursor of the terminal to it's middle, line screen_middle and column 0
        move(screen_middle, 0);

        // Makes the next string that will be printer bold
        standout();
        // Prints string screen_divider
        addstr(screen_divider);
        // Turns off set bold
        standend();

        // Sets the terminal cursor to the location of middle of terminal screen -1 and moves the cursor each time and display a string
        for (c1 = screen_middle + 1; c1 < LINES -1; c1++)
        {
          move(c1,0);
          addstr(terminal_screen[c1]);
        }

        // Sets the terminal cursor to location 0 and moves the cursor eahc time and displays a string.
        for (c1 = 0; c1 < screen_middle; c1++)
        {
          move(c1,0);
          addstr(terminal_screen[c1]);
        }

        // Move Cursor to Lower Left
        move(LINES-1, 0);
        // Clear current line to end of line
        clrtoeol();
        // Update Display
        refresh();
    }

    // Quit ncurses system
    endwin();
    free(screen_divider);
    free(temporary);
    for (c1 = 0; c1 < LINES; c1++)
    {
      free(terminal_screen[c1]);
    }
    free(terminal_screen);
    return 0;
}
