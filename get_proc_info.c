//Author: Siyuan Ji (cs login: siyuan; netid: sji27)
//	  Yifan Mei (cs login: yifanmei; netid: ymei8)

#include "get_proc_info.h"
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

/* Description:
 *   This is a main function to print all outputs we need. If pFlag is zero, we only print 
 *   info for processes with uid the same as user ID; if pFlaf is not zero, we print info 
 *   for the specific process users ask for.
 */

void get_proc_info(char* pid,int pFlag, int sFlag, int UFlag, int SFlag, int vFlag, int cFlag){
  //set dynamic buffersize
  int bufferSize = 10000;
  //set variables ss, SS, UU, cc, vv, path to store the contents of state, stime, utime, cmdline, size, file path
  char* ss = malloc(bufferSize*sizeof(char));
  char* SS = malloc(bufferSize*sizeof(char));
  char* UU = malloc(bufferSize*sizeof(char));
  char* cc = malloc(bufferSize*sizeof(char));
  char* vv = malloc(bufferSize*sizeof(char));  
  char* path = malloc(bufferSize*sizeof(char));
  //only when the pid is not uid for pFlag = 0, the match will change to 0. So we set match = 1 at first.
  int match = 1;
  DIR *dirp;
  struct dirent *dp;
  strcpy(path,"/proc/");
  strcat(path,pid);  
  if((dirp = opendir(path)) != NULL){
    while((dp = readdir(dirp)) != NULL){  

      /* Find the matching uid if pFlag is zero. In get_user_proc function, we focus 
       * on getting all pid in the proc directory. Here, we check which of those pid 
       * are uid*/
        if (!pFlag){
        if (!strcmp(dp->d_name, "status")){
	  char statusPath[bufferSize];
  	  strcpy(statusPath, path);
	  strcat(statusPath, "/status");
          FILE *fp;
	  fp = fopen(statusPath, "r");
	  char str[bufferSize];

	  /* acquire Uid line in the status file */
	  while ((fgets(str,sizeof(str),fp)) != NULL){  
	    if (str[0] == 'U' && str[1] == 'i' && str[2] == 'd'){
 	      break;
	    }
	  } 
	 unsigned int uid = 0;
         sscanf(str, "%*s %d", &uid);

         
	 /* close status file */
	 fclose(fp);

	 /* compare with target uid, print nothing if doesn't match */
	 if(uid != (getuid())){
	    match = 0;
	    break;
	 }
       }      	
     }	
     
      //open stat file
     if(!strcmp(dp->d_name, "stat")){
	char statPath[bufferSize];
	strcpy(statPath,path);
        strcat(statPath, "/stat");
	FILE *fp;
	fp = fopen(statPath, "r");
        if (fp != NULL){
	//get state, stime, utime from the stat file using regular expression.
	  fscanf(fp, "%*s %*s %s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %s %s", ss,SS,UU);
	  fclose(fp);
	}	
 	else {
	  perror("Cannot open the file");
	} 
     }
      
      //open statm file
      if(!strcmp(dp->d_name, "statm")){
  	char statmPath[bufferSize];
	strcpy(statmPath,path);
        strcat(statmPath, "/statm");
	FILE *fp;
	fp = fopen(statmPath, "r");
        if (fp != NULL){
      //get size from the statm file
	  fscanf(fp, "%s",vv);
	  fclose(fp);
	}
 	else {
	  perror("Cannot open the file");
	} 
      }
   
      //open cmdline file
      if(!strcmp(dp->d_name, "cmdline")){
	char cmdPath[bufferSize];
	strcpy(cmdPath,path);
        strcat(cmdPath, "/cmdline");
	FILE *fp;
	fp = fopen(cmdPath, "r");
        if (fp != NULL){
          //get contents in cmdline file
	  while(fgets(cc, sizeof(cc), fp)){
        //make sure cmdline file is not null
	    if (cc != NULL)
	     break;
	  }              
  	  fclose(fp);
	}
 	else {
	  perror("Cannot open the file");
	} 
      }

    }

    //print in the same order as user input
    if (match){
      printf("%s: ", pid);
    if (sFlag)
      printf(" %s", ss);
    if (UFlag)
      printf(" utime=%s ", UU);
    if (SFlag)
      printf(" stime=%s", SS);
    if (vFlag)
      printf(" vmemory=%s ",vv);	
    if (cFlag) 
      printf(" [%s]", cc);
    printf("\n");
    } 
  }
  
  else{
    //catch the exception when the directory is not able to open
    perror("Cannot open this directory");
  }
  

}
