#Authors: Siyuan Ji (cs login: siyuan; netid: sji27)
#	  Yifan Mei (cs login: yifanmei; netid: ymei8)
CFLAG= -Wall -Wextra

cc = gcc

SCAN_BUILD_DIR = scan-build-out

537ps: get_user_proc.o get_proc_info.o option_parser.o
	$(cc) $(CFLAG) -o 537ps get_user_proc.o get_proc_info.o option_parser.o

option_parser.o: option_parser.c 
	$(cc) $(CFLAG) -c option_parser.c

get_proc_info.o: get_proc_info.c
	$(cc) $(CFLAG) -c get_proc_info.c

get_user_proc.o: get_user_proc.c
	$(cc) $(CFLAG) -c get_user_proc.c
clean:
	 rm *.o 537ps 
#
## Run the Clang Static Analyzer
#
scan-build: clean
	scan-build -o $(SCAN_BUILD_DIR) make

#
## View the one scan available using firefox
#
scan-view: scan-build
	firefox -new-window $(SCAN_BUILD_DIR)/*/index.html 
