////////////////////////////////////////////////////////////////////////////////
// Main File:        537ps.c
// This File:        537ps.c
// Other Files:      
// Semester:         CS 537 Fall 2018
//
// Author:           Siyuan Ji
// Email:            sji27@wisc.edu
// CS Login:         siyuan
//
// Author:           Yifan Mei
// Email:            ymei8@wisc.edu
// CS Login:         yifanmei
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          NULL
//
// Online sources:   NULL
//
//////////////////////////// 80 columns wide ///////////////////////////////////

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "get_user_proc.h"
#include "get_proc_info.h"

/* Description:
 *   Parse the options from user and store state for each option, later calling
 *   get_user_proc or get_proc_info depends on whether users call -p or not
 */
int main(int argc, char *argv[]){
  //x_Flag records the choice of users
  int bufferSize = 1000;
  int pFlag = 0;
  //In default, s/S/v are F, U/c are T
  int sFlag = 0;
  int UFlag = 1;
  int SFlag = 0; 
  int vFlag = 0;
  int cFlag = 1;
  char* pid = malloc(bufferSize*sizeof(char));
  int result;

  while((result = getopt(argc, argv, ":p:s::U::S::v::c::")) != -1 ){
    switch (result){
      case 'p':
     //if the argument after -p is not a digit, exit
	if(!atoi(optarg)){
          printf("Error: Argument Is Not Valid!!\n");
          exit(1); 
        }
	// If -p is first called, pFlag is set to one
	else{	
	  strcpy(pid, optarg);	
    	  pFlag = 1;	
      	  break;
	}
      
      case 's':
	  if (optarg != NULL){
	    if (!strcmp("-", optarg)){	       
	      sFlag = 0;
	      break;
	    }  
	    else {
              //if the arguement after -s is not "-", exit
              printf("Error: Argument Is Not Valid!!\n");
              exit(1); 
            }
	  }
	  else{
            sFlag = 1;
	    break;
	  }
	
	
	
      case 'U':
	  UFlag = 1;
	  if (optarg != NULL){  
	    if (!strcmp("-", optarg)){ 
              UFlag = 0;
	      break;  
	    }
	    else {
              //if the arguement after -U is not "-", exit
              printf("Error: Argument Is Not Valid!!\n");
              exit(1); 
	    }
	  }
	break;
      
      case 'S':
  	  if (optarg != NULL){
	    if (!strcmp("-", optarg)){	
	      SFlag = 0;	    
	      break;
	    }
	    else{
              //if the arguement after -S is not "-", exit
              printf("Error: Argument Is Not Valid!!\n");
              exit(1); 
            }
          }
	  else{
            //original is set SFlag to be 0
            SFlag = 1;
	    break;
          }
	 
            
      
      case 'v':
          if (optarg != NULL){
	    if (!strcmp("-", optarg)){	
	      vFlag = 0;
	      break;
	    }
	    else{
              //if the arguement after -v is not "-", exit
              printf("Error: Argument Is Not Valid!!\n");
              exit(1); 
            }	
      	  }
	  else{
            //original is set vFlag to be 0
            vFlag = 1;
	    break;
	  }  
      

      case 'c':
	  cFlag = 1;
	  if (optarg != NULL){		  
	    if (!strcmp("-", optarg)){ 
              cFlag = 0;
	      break;  
	    }
	    else {
              //if the arguement after -c is not "-", exit
              printf("Error: Argument Is Not Valid!!\n");
              exit(1); 
	    }
          }    
        break;      
     
     case '?':
       printf("Invalid Option \n");
       exit(1);

     default:	
       printf("Error: Argument Is Not Valid!!\n");
       exit(1);
    } 
  }
  
  //handle leftover arguments
  if (optind < argc) {
    printf("Error: Invalid Option\n"); 
    exit(1); 
  }
  
  //if there is no -p, search all directories named by digits in proc directory
  if (!pFlag)
    get_user_proc(pFlag, sFlag, UFlag, SFlag, vFlag, cFlag);
  else
    //if there is -p, search specific id
    get_proc_info(pid, pFlag, sFlag, UFlag, SFlag, vFlag, cFlag);
  
  free(pid);
}
