/*
	   Nome: Victor Seixas Locateli
	TIA: 41924983

	Nome: Rodrigo Rodrigues dos Santos Rios
	TIA: 41783174

	Nome: Carla Pollastrini 
	Tia: 32085877 

	Nome: Victor Cardozo Garcia 
	Tia:32068883
 * 
 *
 *
 *
 *
 *
 *
*/ 






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
	T**matrix;
	size_t row;
	size_t column;
}Matrix_t;
typedef struct{
	Matrix_t  m;
	String lcs_result;
	String str1;
	String str2;
}Lcs_t;

void error(FILE *stream,const char *message);
void usage(FILE *stream,const char *program_name);
char * allocate_str(size_t len);
Matrix_t  malloc_2d(size_t row,size_t col);
void free_matrix(Matrix_t m,size_t col);
void fill_lcstable_with_zeroes(Matrix_t m,size_t row ,size_t col);
Lcs_t lcs(Lcs_t lcs);
void calculate_lcs_ptr(Lcs_t **lcs);
void free_string(String str);
#endif // EP_1_H 
