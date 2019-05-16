#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/*
	radamsa 
	-9802510 + 5 
	Segfault 0x0800416
*/

void timeout(){
	puts("No time to waste!");
	exit(0);
}

int parse_expr(void *expression, int *init_pool){
	int counter = 0;
	// Canary set 
	do {
		// CARRY ON HERE 
	} while ( 1 ); 
}

void init_pool(int *pool){
	// zero out 100 bytes ? 
	int counter;
	*pool = 0;
	while (counter < 100){
		pool[counter + 1] = 0;
		counter += 1;
	}
	return;
}

int get_expr(char *expression, int max_size){
	char current_char;
	int read_ret;
	int current_location = 0;

	// not sure how to declare arg pointer expression

	while ( current_location < max_size ) {
		read_ret = read(0, &current_char, 1);
		if ((read_ret == -1) || (current_char == '\n')) {
			break;
		}
		if ((current_char == '+') || (current_char == '-') || (current_char == '*') ||
		 (current_char == '/') || (current_char == '%') || (('/' < current_char && (current_char < ':')))) {
		 	// Why does 
		 	// '/' < current && (current < ':') 
		 	// equate to 
		 	// 0 <= current <= 9
		 	expression[current_location] = current_char;
		 	current_location += 1;
		}
	}

	expression[current_location] = 0;
	return current_location;
}

void calc(){
	int bytes_read; 
	int parse_ret_code;
	int pool; 
	int numbers [100];
	char expression[1024];

	while ( 1 ) {
		bzero(expression, 1024);
		bytes_read = get_expr(&expression, 4);
		if (bytes_read == 0) break;
		init_pool(&pool);
		parse_ret_code = parse_expr(expression, &pool);
	}
}

void main(void){
	signal(SIGALRM, timeout);
	alarm(60);
	puts("=== Welcome to SECPROG calculator ===");
	fflush(stdout);
	calc();
	puts("Merry Christmas!");
	return;
}