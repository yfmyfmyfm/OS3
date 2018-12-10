//Authors: Siyuan Ji (cs login: siyuan; netid: sji27)
//	   Yifan Mei (cs login: yifanmei; netid: ymei8)

#include "get_user_proc.h"
#include "get_proc_info.h"
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

/*Description:
 *   This function is to go through all pid directory and 
 *   call get_proc_info to get output for UID. Comparion 
 *   between userID and UID of each process is completed in the get_proc_info
 */

void get_user_proc(int pFlag,int sFlag,int UFlag,int SFlag,int vFlag,int cFlag){
  
  //set dynamic buffer size
  int bufferSize = 1000;
  //set path to store /proc later
  char* path = malloc(bufferSize*sizeof(char));
  //the directories correspond to /proc
  DIR *mDir;
  //set mFile to check whether each file in mDir is a directory and is full of numbers
  struct dirent* mFile;
  strcpy(path, "/proc/");

  
  if((mDir = opendir(path))== NULL)
    perror("Cannot open directory");
  else{
    //begin search all pid directories in proc directory
    while ((mFile = readdir(mDir)) != NULL){
      //check whether the directory name is full of digits or not
      if (atoi(mFile->d_name)){
    //if the directory is a valid pid directory, call findProc function for further actions.
	get_proc_info(mFile->d_name, pFlag, sFlag, UFlag, SFlag, vFlag, cFlag);
      }
    }
  }
}
