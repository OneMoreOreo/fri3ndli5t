/*
============================================================================
Fri3ndLi5t

Simple program where you can add friends to a list.

References:
https://www.programiz.com/c-programming/c-file-input-output
https://www.cprogramming.com/tutorial/cfileio.html

============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //Include for while loop
#include <string.h>  //Include for strings

// Define Filepath for the binaty file
#define FILEPATH "C:\\Files\\friends.bin"

// -----typedefs -------
typedef struct
{
  char firstname[20];
  char famname[20];
  char pers_number[13]; // yyyymmddnnnc
} PERSON;

// Function declaration (to be extend)
PERSON input_record(void);             // Reads a person’s record.
void write_new_file(PERSON *inrecord); // Creates a file and
                                       // writes the first record
void printfile(void);                  // Prints out all persons in the file
void search_by_firstname(char *name);  // Prints out the person if // in list
void append_file(PERSON *inrecord);    // appends a new person to the file
void search_by_lastname(char *name);   // for searching by last name
bool runningprogram(PERSON *inrecord); // keeps program running
void search_Records();                 // function for giving options for search

int main(int argc, char *argv[])
{

  // Default record in created file
  PERSON newperson = {"Lord", "Megatron", "202001019999"}; // Added when creating new file

  char text[6] = "Hello"; // Output test

  printf("%s \n", text);

  bool runprogram = true; // Bool for while loop

  // Keep program runninguntil input is 5
  while (runprogram)
  {
    runprogram = runningprogram(&newperson); // Send default person as argument
  }
  // write_new_file(&newperson);

  return EXIT_SUCCESS;
}
// Function for menu and getting user options
bool runningprogram(PERSON *inrecord)
{
  bool runprogram = true; // Variable for while loop, false when 5

  int response = 0; // Varaible for user options

  printf("====================\n");
  printf("Hello! Choose From Options\n");
  printf("1. New Record\n");
  printf("2. Add Record\n");
  printf("3. Search Records\n");
  printf("4. Print Records\n");
  printf("5. Exit\n");
  printf("====================\n");
  scanf("%d", &response); // Scan and store user input

  // Switch cases for user input
  switch (response)
  {
  case 1:
    write_new_file(inrecord); // Create new record
    break;
  case 2:
    append_file(inrecord); // Add new record to file
    break;
  case 3:
    search_Records(); // Search in records
    break;
  case 4:
    printfile(); // Print records in console
    break;
  case 5:
    runprogram = false; // Exit program
    break;

  default:
    printf("Incorrect input\n");
    break;
  }

  return runprogram;
}
// Function for creating and inputting to new file
void write_new_file(PERSON *inrecord)
{
  FILE *fptr; // Pointer for file management

  fptr = fopen(FILEPATH, "wb"); // Open for writing to binary file

  if (fptr == NULL) // If no file
  {
    printf("Error");
    exit(1);
  }

  fwrite(inrecord, sizeof(PERSON), 1, fptr); // Write default document to file

  fclose(fptr); // Close FILE function
}

// Add new record to file

void append_file(PERSON *inrecord)
{
  printf("New Record\n"); // Get user input for new document
  printf("Input First Name: \n");
  scanf("%s", inrecord->firstname); // Get First Name
  printf("Input Last Name: \n");
  scanf("%s", inrecord->famname); // Get Last Name
  printf("Input Pers Number: \n");
  scanf("%s", inrecord->pers_number); // Get Pers Number

  FILE *fptr; // Pointer

  fptr = fopen(FILEPATH, "ab"); // Open file for appending to binary file

  if (fptr == NULL) // If no file return
  {
    printf("Error");
    exit(1);
  }

  fwrite(inrecord, sizeof(PERSON), 1, fptr); // Write new document to binary file

  fclose(fptr); // Close
}

// Get User Options for Search Condition
void search_Records()
{
  char searchPerson[20]; // Declare String for User Input
  int option = 0;        // Option for search condition

  printf("============\n");
  printf("Search For Person\n");
  printf("1. Search First Name \n");
  printf("2. Search Last Name \n");
  scanf("%d", &option); // User Option for First or Last Name
  printf("3. Enter Search \n");
  scanf("%s", &searchPerson); // Search Name to Look Up
  printf("============\n");
  // Search for Name
  if (option == 1)
  {
    search_by_firstname(searchPerson); // Search First Name
  }

  else
  {
    search_by_lastname(searchPerson); // Search Last Name
  }
}

// Function for searching by first name
void search_by_firstname(char *name)
{
  FILE *fptr; // Pointer for file management

  printf("Looking for %s\n", name);
  printf("===============Results==============\n");

  fptr = fopen(FILEPATH, "rb"); // Open file for reading binary

  if (fptr == NULL) // If no file found exit
  {
    printf("Error");
    exit(1);
  }

  int count = 0; // Variable for checking number of matches

  PERSON search;
  // strcmp(argv[1], "-h")

  // Scan file
  while (fread(&search, sizeof(PERSON), 1, fptr)) // Scan records in file
  {
    if (!strcmp(search.firstname, name)) // If match print result
    {
      printf("n1: %s\t n2: %s \t n3: %s\n", search.firstname, search.famname, search.pers_number);
      // printf("n1: %s\t n2: %s \t n3: %s\n", num.one, num.two, num.three);
      count++; // Add to variable
    }
  }

  if (count == 0) // No match
  {
    printf("Not Found /n");
  }

  fclose(fptr); // Close
}

// Search last name
void search_by_lastname(char *name)
{
  FILE *fptr; // File pointer for file management

  printf("Looking for %s\n", name);
  printf("===============Results==============\n");

  fptr = fopen(FILEPATH, "rb"); // Open file for reading binary file

  if (fptr == NULL) // If no file
  {
    printf("Error");
    exit(1);
  }

  int count = 0;

  PERSON search; // Declare document for searching file
  // strcmp(argv[1], "-h")

  while (fread(&search, sizeof(PERSON), 1, fptr)) // Scan all documents in file
  {
    if (!strcmp(search.famname, name)) // If match found print result
    {
      printf("n1: %s\t n2: %s \t n3: %s\n", search.firstname, search.famname, search.pers_number);
      // printf("n1: %s\t n2: %s \t n3: %s\n", num.one, num.two, num.three);
      count++; // Add to variable
    }
  }

  if (count == 0) // No match
  {
    printf("Not Found /n");
  }

  fclose(fptr); // Close pointer
}

// Function for printing all documents in file
void printfile(void)
{

  FILE *fptr; // File pointer

  fptr = fopen(FILEPATH, "rb"); // Reading binary file

  if (fptr == NULL) // If no document exit
  {
    printf("Error");
    exit(1);
  }

  PERSON printList; // Declare document for reading

  while (fread(&printList, sizeof(PERSON), 1, fptr)) // Scan and print all documents in file
  {
    printf("n1: %s\t n2: %s \t n3: %s\n", printList.firstname, printList.famname, printList.pers_number);
  }

  fclose(fptr);
}
