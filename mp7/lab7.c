/* lab7.c template
 * Rodrigo Ignacio Rojas Garcia
 * rrojas
 * ECE 2220, Fall 2016
 * MP7
 * Purpose: The purpose of this program is to model Mission Control guiding three space crafts to Mars and back to Earth.
            Another purpose it is for the student to explore processes such as fork() and wait().
            Also, the purpose was to be able to handle the use of signal functions such as signal(), alarm(), pause(), and kill().
            Finally, it was to demonstrate how to open different terminals and how to write to them.

  Assumptions: User knows all Mission Control commands.
               User knows that Rover can be launched only one time.
               User knows that Way points decrease every two seconds and distance every one second.
               User knows that to return to Earth, Mars have to be reached, Rover has to be launched, and have enough Way Points for both travels.

 * Misssion Control commands: The Mission Control commands are as follows:
 *				ln) Instructs space craft n to launch its Rover. n is one of 1, 2, or 3.
 *				kn) Instructs space craft n to cancel its mission (the process is killed). n is 1, 2, or 3.
 *				tn) Transmits 10 new way points to space craft n.
 *   			 	q) Exits the program.
 *
 * Known bugs: No bugs detected.
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

// Global Variable Declaration Section
#define NUMTTYS 4
#define MAXLINE 100
FILE *fpt[NUMTTYS];
int travel;
int release;
int refill;
int quit_mission;
int terminate_program;

// Function Declaration Section
void alarmnotice(int signum)
{
  travel = 1;
}

void Rover(int signum)
{
  release = 1;
}

void Refill(int signum)
{
  refill = 1;
}

void MissionTerminated(int signum)
{
  quit_mission = 1;
}

void TerminateProgram(int signum)
{
  terminate_program = 1;
}


void SpaceShipOne(int number, int distance, int fuel)
{
  // Variable Declaration Section
  int reset = 0;
  int distance_to_Earth = distance;
  int release_completed = 0;
  // Sets alarm signal
  signal(SIGALRM, alarmnotice);
  // Sets signal to launch Rover
  signal(SIGUSR1, Rover);
  // Sets signal to add fuel to Space Craft
  signal(SIGUSR2, Refill);
  // Sets signal to abort the mission
  signal(SIGQUIT, MissionTerminated);
  // Sets signal to termiante the whole program
  signal(SIGKILL, TerminateProgram);
  // Prints PID number and random distance from Mars
  fprintf(fpt[number], "Space Craft %d initiating mission. Distance from Mars %2d\n", number, distance);
  // Sets alarm to one second.
  alarm(1);

  // While the distance AND the fuel do not reach zero, the loop will run
  while (1)
  {
    // Pauses code after pause() function until alarm signal is detected
    pause();
    // If the alarm is set off, it resets the alarm, and adds one to variable reset
    if (travel > 0)
    {
      if (distance > 0)
      {
        // Prints starting distace fom Mars and space craft's PID number
        fprintf(fpt[number], "Distance of Space Craft %2d from Mars %2d || Way Points: %2d\n", number, distance, fuel);
        // Decreases distance from Mars each second
        distance--;
        travel = 0;
        alarm(1);
        reset++;
        // If reset reaches value of two, means that two seconds have passed and fuel is decremented
        if (reset == 2)
        {
          fuel--;
          reset = 0;
        }
        // If fuel reaches a value less than five, it will print following message every second
        if (fuel < 5)
        {
          fprintf(fpt[number], "Houston, we have a problem!\n");
        }
        // If fuel reaches 0, it means it will be lost in space, therefore varible lost set to 2.
        if (fuel == 0)
        {
          fprintf(fpt[number], "Space craft %d. Lost in Space.\n", number);
          exit(1);
        }
        // If user releases the Rover to early, space craft is destroyed
        if (release == 1)
        {
          fprintf(fpt[number], "Space Craft %d has been self-destroyed. Mission failed.\n", number);
          exit(2);
        }
        // If user decideds to abort mission, this if statement runs
        if (quit_mission == 1)
        {
          fprintf(fpt[number], "Mission of Space Craft %d, has been cancelled.\n", number);
          exit(SIGQUIT);
        }
        // If user decides to terminate program completely, this runs
        if (terminate_program == 1)
        {
          exit(SIGKILL);
        }
        // If Refill signal called, fuel adds ten to it
        if (refill == 1)
        {
          fuel += 10;
          refill = 0;
        }
      }

      // If the distance reached Mars orbit and the fuel has not ran out, this runs
      if (distance == 0 && release_completed != 1)
      {
        fprintf(fpt[number], "Space craft %d to Mission Control: entered orbit. Please send signal to launch Rover. || Way Points: %2d\n", number, fuel);
        // If signal to release is entered, Rover is released.
        if (release == 1)
        {
          fprintf(fpt[number], "Rover has been launched. Distance to Earth: %2d\n", distance_to_Earth);
          release_completed = 1;
          release = 0;
        }
        // Sets travel to 0 and resets the alarm and adds one to reset
        travel = 0;
        alarm(1);
        reset++;
        // If two seconds have passed, fuel is decreased and reset is set to 0.
        if (reset == 2)
        {
          fuel--;
          reset = 0;
        }
        // If Refill signal called, fuel adds ten to it
        if (refill == 1)
        {
          fuel += 10;
          refill = 0;
        }
        // If user decides to terminate program completely, this runs
        if (terminate_program == 1)
        {
          exit(SIGKILL);
        }
        // If user decideds to abort mission, this if statement runs
        if (quit_mission == 1)
        {
          fprintf(fpt[number], "Mission of Space Craft %d, has been cancelled.\n", number);
          exit(SIGQUIT);
        }
        if (fuel == 0)
        {
          fprintf(fpt[number], "Space craft %d. Lost in Space.\n", number);
          exit(1);
        }
      }

      // If the release has been succesfull, this if statement runs
      if (release_completed == 1)
      {
        fprintf(fpt[number], "Distance of Space Craft %d to Earth: %2d || Way Points: %2d\n", number, distance_to_Earth, fuel);
        // Sets travel to 0 and resets the alarm and adds one to reset
        distance_to_Earth--;
        travel = 0;
        alarm(1);
        reset++;
        // If two seconds have passed, fuel is decreased and reset is set to 0.
        if (reset == 2)
        {
          fuel--;
          reset = 0;
        }
        // If Refill signal called, fuel adds ten to it
        if (refill == 1)
        {
          fuel += 10;
          refill = 0;
        }
        // If user decides to terminate program completely, this runs
        if (terminate_program == 1)
        {
          exit(SIGKILL);
        }
        // If user decideds to abort mission, this if statement runs
        if (quit_mission == 1)
        {
          fprintf(fpt[number], "Mission of Space Craft %d, has been cancelled.\n", number);
          exit(SIGQUIT);
        }
        // If the distance to Earth is not zero, and fuel has ran out, program is terminated.
        if (distance_to_Earth != 0 && fuel == 0)
        {
          fprintf(fpt[number], "Space craft %d. Lost in space.\n", number);
          exit(1);
        }
        // If the release of Rover command is typed by the user again, Space Craft will be self-destroyed
        if (release == 1)
        {
          fprintf(fpt[number], "Space craft %d has been self-destroyed. Mission failed.\n", number);
          exit(2);
        }
        // If Earth has been reached by the Space Craft and there is fuel left, Mission is completed.
        if (distance_to_Earth == 0 && fuel != 0)
        {
          fprintf(fpt[number], "Space craft %d has returned to Earth successfully.\n", number);
          exit(4);
        }
      }
    }
  }
}

void SpaceShipTwo(int number, int distance, int fuel)
{
  // Variable Declaration Section
  int reset = 0;
  int distance_to_Earth = distance;
  int release_completed = 0;
  // Sets alarm signal
  signal(SIGALRM, alarmnotice);
  // Sets signal to launch Rover
  signal(SIGUSR1, Rover);
  // Sets signal to add fuel to Space Craft
  signal(SIGUSR2, Refill);
  // Sets signal to abort the mission
  signal(SIGQUIT, MissionTerminated);
  // Sets signal to termiante the whole program
  signal(SIGKILL, TerminateProgram);
  // Prints PID number and random distance from Mars
  fprintf(fpt[number], "Space Craft %d initiating mission. Distance from Mars %2d\n", number, distance);
  // Sets alarm to one second.
  alarm(1);

  // While the distance AND the fuel do not reach zero, the loop will run
  while (1)
  {
    // Pauses code after pause() function until alarm signal is detected
    pause();
    // If the alarm is set off, it resets the alarm, and adds one to variable reset
    if (travel > 0)
    {
      if (distance > 0)
      {
        // Prints starting distace fom Mars and space craft's PID number
        fprintf(fpt[number], "Distance of Space Craft %2d from Mars %2d || Way Points: %2d\n", number, distance, fuel);
        // Decreases distance from Mars each second
        distance--;
        travel = 0;
        alarm(1);
        reset++;
        // If reset reaches value of two, means that two seconds have passed and fuel is decremented
        if (reset == 2)
        {
          fuel--;
          reset = 0;
        }
        // If fuel reaches a value less than five, it will print following message every second
        if (fuel < 5)
        {
          fprintf(fpt[number], "Houston, we have a problem!\n");
        }
        // If fuel reaches 0, it means it will be lost in space, therefore varible lost set to 2.
        if (fuel == 0)
        {
          fprintf(fpt[number], "Space craft %d. Lost in Space.\n", number);
          exit(1);
        }
        // If user releases the Rover to early, space craft is destroyed
        if (release == 1)
        {
          fprintf(fpt[number], "Space Craft %d has been self-destroyed. Mission failed.\n", number);
          exit(2);
        }
        // If user decideds to abort mission, this if statement runs
        if (quit_mission == 1)
        {
          fprintf(fpt[number], "Mission of Space Craft %d, has been cancelled.\n", number);
          exit(SIGQUIT);
        }
        // If user decides to terminate program completely, this runs
        if (terminate_program == 1)
        {
          exit(SIGKILL);
        }
        // If Refill signal called, fuel adds ten to it
        if (refill == 1)
        {
          fuel += 10;
          refill = 0;
        }
      }

      // If the distance reached Mars orbit and the fuel has not ran out, this runs
      if (distance == 0 && release_completed != 1)
      {
        fprintf(fpt[number], "Space craft %d to Mission Control: entered orbit. Please send signal to launch Rover. || Way Points: %2d\n", number, fuel);
        // If signal to release is entered, Rover is released.
        if (release == 1)
        {
          fprintf(fpt[number], "Rover has been launched. Distance to Earth: %2d\n", distance_to_Earth);
          release_completed = 1;
          release = 0;
        }
        // Sets travel to 0 and resets the alarm and adds one to reset
        travel = 0;
        alarm(1);
        reset++;
        // If two seconds have passed, fuel is decreased and reset is set to 0.
        if (reset == 2)
        {
          fuel--;
          reset = 0;
        }
        // If Refill signal called, fuel adds ten to it
        if (refill == 1)
        {
          fuel += 10;
          refill = 0;
        }
        // If user decides to terminate program completely, this runs
        if (terminate_program == 1)
        {
          exit(SIGKILL);
        }
        // If user decideds to abort mission, this if statement runs
        if (quit_mission == 1)
        {
          fprintf(fpt[number], "Mission of Space Craft %d, has been cancelled.\n", number);
          exit(SIGQUIT);
        }
        if (fuel == 0)
        {
          fprintf(fpt[number], "Space craft %d. Lost in Space.\n", number);
          exit(1);
        }
      }

      // If the release has been succesfull, this if statement runs
      if (release_completed == 1)
      {
        fprintf(fpt[number], "Distance of Space Craft %d to Earth: %2d || Way Points: %2d\n", number, distance_to_Earth, fuel);
        // Sets travel to 0 and resets the alarm and adds one to reset
        distance_to_Earth--;
        travel = 0;
        alarm(1);
        reset++;
        // If two seconds have passed, fuel is decreased and reset is set to 0.
        if (reset == 2)
        {
          fuel--;
          reset = 0;
        }
        // If Refill signal called, fuel adds ten to it
        if (refill == 1)
        {
          fuel += 10;
          refill = 0;
        }
        // If user decides to terminate program completely, this runs
        if (terminate_program == 1)
        {
          exit(SIGKILL);
        }
        // If user decideds to abort mission, this if statement runs
        if (quit_mission == 1)
        {
          fprintf(fpt[number], "Mission of Space Craft %d, has been cancelled.\n", number);
          exit(SIGQUIT);
        }
        // If the distance to Earth is not zero, and fuel has ran out, program is terminated.
        if (distance_to_Earth != 0 && fuel == 0)
        {
          fprintf(fpt[number], "Space craft %d. Lost in space.\n", number);
          exit(1);
        }
        // If the release of Rover command is typed by the user again, Space Craft will be self-destroyed
        if (release == 1)
        {
          fprintf(fpt[number], "Space craft %d has been self-destroyed. Mission failed.\n", number);
          exit(2);
        }
        // If Earth has been reached by the Space Craft and there is fuel left, Mission is completed.
        if (distance_to_Earth == 0 && fuel != 0)
        {
          fprintf(fpt[number], "Space craft %d has returned to Earth successfully.\n", number);
          exit(4);
        }
      }
    }
  }
}

void SpaceShipThree(int number, int distance, int fuel)
{
  // Variable Declaration Section
  int reset = 0;
  int distance_to_Earth = distance;
  int release_completed = 0;
  // Sets alarm signal
  signal(SIGALRM, alarmnotice);
  // Sets signal to launch Rover
  signal(SIGUSR1, Rover);
  // Sets signal to add fuel to Space Craft
  signal(SIGUSR2, Refill);
  // Sets signal to abort the mission
  signal(SIGQUIT, MissionTerminated);
  // Sets signal to termiante the whole program
  signal(SIGKILL, TerminateProgram);
  // Prints PID number and random distance from Mars
  fprintf(fpt[number], "Space Craft %d initiating mission. Distance from Mars %2d\n", number, distance);
  // Sets alarm to one second.
  alarm(1);

  // While the distance AND the fuel do not reach zero, the loop will run
  while (1)
  {
    // Pauses code after pause() function until alarm signal is detected
    pause();
    // If the alarm is set off, it resets the alarm, and adds one to variable reset
    if (travel > 0)
    {
      if (distance > 0)
      {
        // Prints starting distace fom Mars and space craft's PID number
        fprintf(fpt[number], "Distance of Space Craft %2d from Mars %2d || Way Points: %2d\n", number, distance, fuel);
        // Decreases distance from Mars each second
        distance--;
        travel = 0;
        alarm(1);
        reset++;
        // If reset reaches value of two, means that two seconds have passed and fuel is decremented
        if (reset == 2)
        {
          fuel--;
          reset = 0;
        }
        // If fuel reaches a value less than five, it will print following message every second
        if (fuel < 5)
        {
          fprintf(fpt[number], "Houston, we have a problem!\n");
        }
        // If fuel reaches 0, it means it will be lost in space, therefore varible lost set to 2.
        if (fuel == 0)
        {
          fprintf(fpt[number], "Space craft %d. Lost in Space.\n", number);
          exit(1);
        }
        // If user releases the Rover to early, space craft is destroyed
        if (release == 1)
        {
          fprintf(fpt[number], "Space Craft %d has been self-destroyed. Mission failed.\n", number);
          exit(2);
        }
        // If user decideds to abort mission, this if statement runs
        if (quit_mission == 1)
        {
          fprintf(fpt[number], "Mission of Space Craft %d, has been cancelled.\n", number);
          exit(SIGQUIT);
        }
        // If user decides to terminate program completely, this runs
        if (terminate_program == 1)
        {
          exit(SIGKILL);
        }
        // If Refill signal called, fuel adds ten to it
        if (refill == 1)
        {
          fuel += 10;
          refill = 0;
        }
      }

      // If the distance reached Mars orbit and the fuel has not ran out, this runs
      if (distance == 0 && release_completed != 1)
      {
        fprintf(fpt[number], "Space craft %d to Mission Control: entered orbit. Please send signal to launch Rover. || Way Points: %2d\n", number, fuel);
        // If signal to release is entered, Rover is released.
        if (release == 1)
        {
          fprintf(fpt[number], "Rover has been launched. Distance to Earth: %2d\n", distance_to_Earth);
          release_completed = 1;
          release = 0;
        }
        // Sets travel to 0 and resets the alarm and adds one to reset
        travel = 0;
        alarm(1);
        reset++;
        // If two seconds have passed, fuel is decreased and reset is set to 0.
        if (reset == 2)
        {
          fuel--;
          reset = 0;
        }
        // If Refill signal called, fuel adds ten to it
        if (refill == 1)
        {
          fuel += 10;
          refill = 0;
        }
        // If user decides to terminate program completely, this runs
        if (terminate_program == 1)
        {
          exit(SIGKILL);
        }
        // If user decideds to abort mission, this if statement runs
        if (quit_mission == 1)
        {
          fprintf(fpt[number], "Mission of Space Craft %d, has been cancelled.\n", number);
          exit(SIGQUIT);
        }
        if (fuel == 0)
        {
          fprintf(fpt[number], "Space craft %d. Lost in Space.\n", number);
          exit(1);
        }
      }

      // If the release has been succesfull, this if statement runs
      if (release_completed == 1)
      {
        fprintf(fpt[number], "Distance of Space Craft %d to Earth: %2d || Way Points: %2d\n", number, distance_to_Earth, fuel);
        // Sets travel to 0 and resets the alarm and adds one to reset
        distance_to_Earth--;
        travel = 0;
        alarm(1);
        reset++;
        // If two seconds have passed, fuel is decreased and reset is set to 0.
        if (reset == 2)
        {
          fuel--;
          reset = 0;
        }
        // If Refill signal called, fuel adds ten to it
        if (refill == 1)
        {
          fuel += 10;
          refill = 0;
        }
        // If user decides to terminate program completely, this runs
        if (terminate_program == 1)
        {
          exit(SIGKILL);
        }
        // If user decideds to abort mission, this if statement runs
        if (quit_mission == 1)
        {
          fprintf(fpt[number], "Mission of Space Craft %d, has been cancelled.\n", number);
          exit(SIGQUIT);
        }
        // If the distance to Earth is not zero, and fuel has ran out, program is terminated.
        if (distance_to_Earth != 0 && fuel == 0)
        {
          fprintf(fpt[number], "Space craft %d. Lost in space.\n", number);
          exit(1);
        }
        // If the release of Rover command is typed by the user again, Space Craft will be self-destroyed
        if (release == 1)
        {
          fprintf(fpt[number], "Space craft %d has been self-destroyed. Mission failed.\n", number);
          exit(2);
        }
        // If Earth has been reached by the Space Craft and there is fuel left, Mission is completed.
        if (distance_to_Earth == 0 && fuel != 0)
        {
          fprintf(fpt[number], "Space craft %d has returned to Earth successfully.\n", number);
          exit(4);
        }
      }
    }
  }
}

int main(int argc, char *argv[])
{
		// Variable Declaration Section
    int ttyindex;
    char strDev[100];
    int Terminal[NUMTTYS];
    int terminal_count = 0;
    signal(SIGKILL, TerminateProgram);

		// Checks to see that the number of terminals is 4, if not, displays this message
    if (argc != NUMTTYS+1)
    {
        printf("Usage: ./lab7 1 2 3 4, where the numbers are the terminal pts values\n");
        exit(1);
    }

    // Determine which ttys are open and available to this user
    for (terminal_count = 0; terminal_count < NUMTTYS; terminal_count++)
    {
      ttyindex = -1;
      ttyindex = atoi(argv[terminal_count+1]);
			// If the number of terminal given is less than 1, it will display error.
      if (ttyindex < 1)
			{
        printf("invalid terminal number %s\n", argv[terminal_count+1]);
        exit(1);
      }
			//Stores number of terminal into ttyindex
			sprintf(strDev, "/dev/pts/%d", ttyindex);
			//Stores the number of the terminal into terminal[terminal_count]
			if ((fpt[terminal_count] = fopen(strDev,"w")) != NULL)
			{
	  		Terminal[terminal_count] = ttyindex;
			}
			// If terminal cannot be written to, error is displayed.
			else
			{
  			printf("failed to open terminal %s\n", strDev);
    		exit(1);
  		}
    }

    // Displays the number of terminals and their corresponding number.
    for (ttyindex=0; ttyindex < terminal_count; ttyindex++)
    {
			// Prints the terminal witht their corrisponding assigned number.
			printf("Terminal[%d] = %d.\n", ttyindex, Terminal[ttyindex]);
			// Prints message in each terminal and displaying which terminal they are on the list (0-3)
      fprintf(fpt[ttyindex], "Hello terminal %d, your are %d in my list.\n", Terminal[ttyindex], ttyindex);
    }

    // Variable Declaration Section
    int ship1;
    int ship2;
    int ship3;
    int process1;
    int process2;
    int process3;
    int process_num1;
    int process_num2;
    int process_num3;
    int number = 0;
    int missioncontrol;
    int fuel;
    int distance;
    char line[MAXLINE];
    char command[MAXLINE];

    // Child1 is initilized meaning that the program is cloned.
		ship1 = fork();
    // Ship1 process
    if (ship1 == 0)
    {
      fuel = 10;
      number = 1;
      srand48(number);
      distance = (drand48() * 30) + 30;
      SpaceShipOne(number, distance, fuel);
    }
    // Parent process
    else
    {
      ship2 = fork();
      // Ship2 process
      if (ship2 == 0)
      {
        fuel = 10;
        number = 2;
        srand48(number);
        distance = (drand48() * 30) + 30;
        SpaceShipTwo(number, distance, fuel);
      }
      // Parent process
      else
      {
        ship3 = fork();
        // Ship3 process
        if (ship3 == 0)
        {
          fuel = 10;
          number = 3;
          srand48(number);
          distance = (drand48() * 30) + 30;
          SpaceShipThree(number, distance, fuel);
        }
        // Parent process
        else
        {
          missioncontrol = fork();
          // Misison control process
          if (missioncontrol == 0)
          {
              // Infinite loop that will request user to enter a command.
              while(1)
              {
                // Allows user to enter either  ln, kn, tn, or q commands
                fgets(line, MAXLINE, stdin);
                sscanf(line, "%s", command);
                // If user enters "ln" command, sends signal to release the Rover to desired Space Craft
                if (strcmp(command, "l1") == 0)
                {
                  kill(ship1, SIGUSR1);
                }
                if (strcmp(command, "l2") == 0)
                {
                  kill(ship2, SIGUSR1);
                }
                if (strcmp(command, "l3") == 0)
                {
                  kill(ship3, SIGUSR1);
                }
                // If user enters "tn" command, sends signal to add 10 to the way points to desired Space Craft
                if (strcmp(command, "t1") == 0)
                {
                  kill(ship1, SIGUSR2);
                }
                if (strcmp(command, "t2") == 0)
                {
                  kill(ship2, SIGUSR2);
                }
                if (strcmp(command, "t3") == 0)
                {
                  kill(ship3, SIGUSR2);
                }
                // If user enters "kn" command, sends signal to abort mission of desired Space Craft
                if (strcmp(command, "k1") == 0)
                {
                  kill(ship1, SIGQUIT);
                }
                if (strcmp(command, "k2") == 0)
                {
                  kill(ship2, SIGQUIT);
                }
                if (strcmp(command, "k3") == 0)
                {
                  kill(ship3, SIGQUIT);
                }
                // If user enters "q" command, program is automatically terminated
                if (strcmp(command, "q") == 0)
                {
                  kill(ship1, SIGKILL);
                  kill(ship2, SIGKILL);
                  kill(ship3, SIGKILL);
                  kill(missioncontrol, SIGKILL);
                  kill(getppid(), SIGKILL);
                }
              }
          }
          // Parent process
          else
          {
            // Variable processn will store the PID number of each Space Craft depending on which one finishes first, and process_num will store
            //
            process1 = wait(&process_num1);
            process2 = wait(&process_num2);
            process3 = wait(&process_num3);
            process_num1 = process_num1 >> 8;
            process_num2 = process_num2 >> 8;
            process_num3 = process_num3 >> 8;
            // Determines which Space Craft is which
            if (process1 == ship1)
            {
              process1 = 1;
            }
            if (process1 == ship2)
            {
              process1 = 2;
            }
            if (process1 == ship3)
            {
              process1 = 3;
            }
            if (process2 == ship1)
            {
              process2 = 1;
            }
            if (process2 == ship2)
            {
              process2 = 2;
            }
            if (process2 == ship3)
            {
              process2 = 3;
            }
            if (process3 == ship1)
            {
              process3 = 1;
            }
            if (process3 == ship2)
            {
              process3 = 2;
            }
            if (process3 == ship3)
            {
              process3 = 3;
            }
            // If any of the Space Crafts run out of fuel and are lost in space, process_num will return 1 and this message will be printed.
            if (process_num1 == 1)
            {
              printf("Vaya Con Dios, Space craft %d.\n", process1);
            }
            if (process_num2 == 1)
            {
              printf("Vaya Con Dios, Space craft %d.\n", process2);
            }
            if (process_num3 == 1)
            {
              printf("Vaya Con Dios, Space craft %d.\n", process3);
            }
            // If any of the Space Crafts launched their Rover too early, twice, or not at all.
            if (process_num1 == 2)
            {
              printf("Space craft %d, self-destroyed.\n", process1);
            }
            if (process_num2 == 2)
            {
              printf("Space craft %d, self-destroyed.\n", process2);
            }
            if (process_num3 == 2)
            {
              printf("Space craft %d, self-destroyed.\n", process3);
            }
            if (process_num1 == 3)
            {
              printf("Terminated Space Craft %d.\n", process1);
            }
            if (process_num2 == 3)
            {
              printf("Terminated Space Craft %d.\n", process2);
            }
            if (process_num3 == 3)
            {
              printf("Terminated Space Craft %d.\n", process3);
            }
            // If any of the Space Crafts return to Earth, this displays
            if (process_num1 == 4)
            {
              printf("Welcome home, Space craft %d.\n", process1);
            }
            if (process_num2 == 4)
            {
              printf("Welcome home, Space craft %d.\n", process2);
            }
            if (process_num3 == 4)
            {
              printf("Welcome home, Space craft %d.\n", process3);
            }
            // If all Space Crafts return to Earth, prints this
            if (process_num1 == 4 && process_num2 == 4 && process_num3 == 4)
            {
              printf("Congratulations team: Mission succesfull.\n");
              kill(missioncontrol, SIGKILL);
            }
            // If not all of Space Crafts reutrned to Earth, prints this
            else
            {
              printf("Mission failed.\n");
              kill(missioncontrol, SIGKILL);
            }
          }
        }
      }
    }

		// Parent process which closes the information
    for (ttyindex=0; ttyindex < terminal_count; ttyindex++)
    {
			fclose(fpt[ttyindex]);
    }
		// Terminates the program.
    exit(EXIT_SUCCESS);
}
