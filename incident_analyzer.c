#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct to store values from the dataset 
typedef struct{
    char number[30];
    char incident_state[30];
    char made[30];
    char opened[30];
    char impact[30];
    char urgency[30];
    char priority[30];
    char knowledge[30];
    char resolved[30];
    char closed[30];
    char vendor[30];
    char product[30];
    char country[30];
} Data;

// function prototypes
void completeTask(FILE *output, Data lines[], int task, int size);
void taskLoop(FILE *output, Data lines[], int task, int size);
void threeLine(FILE *output, Data lines[], int val);
void fourLine(FILE *output, Data lines[], int val);
void fullLine(FILE *output, Data lines[], int val);
void applyFilters(FILE *output, Data lines[], int task, int val);
int storeVals(FILE *input, Data data_line[]);

/**
 * Function: main
 * --------------
 * @brief The main function and entry point of the program.
 *
 * @return int 0: No errors; 1: Errors produced.
 */
int main(int argc, char *argv[]) {
    
    // variable definitions
    Data data_line[8002]; // array of each row
    int size; // size counter for the array
    int task; // task number
    FILE* input_file; // input csv file/dataset
    FILE* output_file; // output csv file

    // check if a task was given
    if (argc < 2) {
        printf("Must enter a task.\n");
        return 1;
    } // if

    // get the task number from CLI
    sscanf(argv[1], "--TASK=%d", &task);
    
    // open input file to read
    input_file = fopen("data/202605_dataset.csv", "r");

    if (input_file == NULL){
        printf("Unable to open the file for reading.\n");
        return 1; // exit since failure
    } // if

    // open output file to write
    output_file = fopen("output.csv", "w");

    if (output_file == NULL){
        printf("Unable to open the file for writing.\n");
        return 1; // exit since failure
    } // if

    // get the values from the dataset and store the array size
    size = storeVals(input_file, data_line);
    
    // proceed to create the correct output by task
    completeTask(output_file, data_line, task, size);
    
    // close the files
    fclose(output_file);
    fclose(input_file);

    // end program
    return 0;

} // main

// call the loop using the size according to task
void completeTask(FILE *output, Data lines[], int task, int size){

    // determine the task
    if (task == 1) {
        taskLoop(output, lines, task, 1); // only headers
    } else if (task == 2) {
        taskLoop(output, lines, task, 6); // first five
    } else {
        taskLoop(output, lines, task, size); // 3-5 use whole array
    } // else

} // completeTask

// print the correct lines from the file to output.csv
void taskLoop(FILE *output, Data lines[], int task, int size){
    
    // iterrate through the array and determine which lines get printed
    for (int j = 0; j < size; j++) {
        applyFilters(output, lines, task, j);
    } // for

} // taskLoop

// determine if the line gets printed to output.csv
void applyFilters(FILE *output, Data lines[], int task, int val){
    
    // sort conditions by task
    if (task == 3) {
        // either print the headings or rows with Canada
        if (val == 0 || strcmp(lines[val].country, "Canada") == 0) {
            fullLine(output, lines, val);
        } // if
    } else if (task == 4) {
        // either print headers or rows with Canada, but not all columns
        if (val == 0 || strcmp(lines[val].country, "Canada") == 0) {
            threeLine(output, lines, val);
        } // if
    } else if (task == 5) {
        // either print headers or rows with Canada and Awaiting User Info, but not all columns
        if (val == 0 || (strcmp(lines[val].country, "Canada") == 0 && strcmp(lines[val].incident_state, "Awaiting User Info") == 0)) {
            fourLine(output, lines, val);
        } // if
    } else {
        // print full line to file (task 1-2)
        fullLine(output, lines, val);
    } // else

} // applyFilters

// print number, vendor, and country to output.csv
void threeLine(FILE *output, Data lines[], int val){
    
    fprintf(output, "%s,%s,%s\n", 
        lines[val].number, lines[val].vendor, lines[val].country);

} // threeLine

// print number, knowledge, product, and country to output.csv
void fourLine(FILE *output, Data lines[], int val){
    
    fprintf(output, "%s,%s,%s,%s\n", 
        lines[val].number, lines[val].knowledge, 
        lines[val].product, lines[val].country);

} // fourLine

// print all columns to output.csv
void fullLine(FILE *output, Data lines[], int val){
    
    fprintf(output, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", 
        lines[val].number, lines[val].incident_state, 
        lines[val].made, lines[val].opened, lines[val].impact, lines[val].urgency, 
        lines[val].priority, lines[val].knowledge, lines[val].resolved, lines[val].closed, 
        lines[val].vendor, lines[val].product, lines[val].country);

} // fullLine

// store values from dataset into the struct array
int storeVals(FILE *input, Data data_line[]) {

    // variable definitions
    char line[390]; // to hold one line from the input file
    char *sp; // string pointer for finding terminating points
    int i; // index and size counter

    // iterrate through the data line by line and store the values
    while(fgets(line, 390, input) != NULL){
        
        // store number
        sp = strtok(line, ",");
        strcpy(data_line[i].number, sp);
            
        //store incident_state
        sp = strtok(NULL, ",");
        strcpy(data_line[i].incident_state, sp);
         
        // store made_sla
        sp = strtok(NULL, ",");
        strcpy(data_line[i].made, sp);
            
        // store opened_at
        sp = strtok(NULL, ",");
        strcpy(data_line[i].opened, sp);

        // store impact
        sp = strtok(NULL, ",");
        strcpy(data_line[i].impact, sp);

        // store urgency
        sp = strtok(NULL, ",");
        strcpy(data_line[i].urgency, sp);

        // store priority
        sp = strtok(NULL, ",");
        strcpy(data_line[i].priority, sp);

        // store knowledge
        sp = strtok(NULL, ",");
        strcpy(data_line[i].knowledge, sp);

        // store resolved_at
        sp = strtok(NULL, ",");
        strcpy(data_line[i].resolved, sp);

        // store closed_at
        sp = strtok(NULL, ",");
        strcpy(data_line[i].closed, sp);

        // store vendor
        sp = strtok(NULL, ",");
        strcpy(data_line[i].vendor, sp);

        // store product
        sp = strtok(NULL, ",");
        strcpy(data_line[i].product, sp);

        // store country
        sp = strtok(NULL, "\n");
        strcpy(data_line[i].country, sp);
        
        i++; // increment counter

    } // while

    return i;

} // storeVals

