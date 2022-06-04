#ifndef EP_1_H
#define EP_1_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#define T int 
#define N 1000 
typedef struct {
	char *str;
	size_t len;
}String;

typedef struct{
	T ** matrix;
	char *lcs_result;
	char *str1;
	char *str2;
}lcs_t;

void error(FILE *stream,const char *message);
void usage(FILE *stream,const char *program_name);
char * allocate_str(size_t len);
T ** malloc_2d(size_t row,size_t col);
void free_matrix(T **matrix,size_t col);
void fill_lcstable_with_zeroes(T **LCS_table,size_t row ,size_t col);
lcs_t lcs(lcs_t lcs);
void calculate_lcs_ptr(lcs_t **lcs);

#endif // EP_1_H 
