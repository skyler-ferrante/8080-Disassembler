#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include "opcodes.h"

// printf hex format
#define HEX "%02hhx"

int main(int argc, char** argv){
	if(argc != 2){
		printf("Usage: %s hexdump\n",argv[0]);
		return 1;
	}	
	
	int fd = open(argv[1], O_RDONLY);
	if( fd == -1 ) {
		printf("Could not open file: %s\n", argv[1]);
		return 1;
	}

	int bytes_read = 0;
	
	// One byte for opcode
	// 0, 1, or 2 bytes for arguments
	unsigned char opcode;
	unsigned char arguments[2];

	// Read one instruction at a time, until EOF
	while( read(fd, &opcode, 1) ){
		// Print current address
		printf("%04hx ", bytes_read);

		int size = opcodes[opcode].size;
		printf("%s ", opcodes[opcode].name);

		if(size == 2){
			read(fd, arguments, 1);
			printf("0x" HEX, arguments[0]);
		}else if(size == 3){
			read(fd,arguments, 2);
			printf("0x" HEX HEX, arguments[1], arguments[0]);
		}
		
		printf("\n");
		bytes_read += size;
	}
}
