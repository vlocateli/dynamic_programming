/*

	Nome: Victor Seixas Locateli
	TIA: 41924983

	Nome: Rodrigo Rodrigues dos Santos Rios
	TIA: 41783174

	Nome: Carla Pollastrini
	Tia: 32085877 

	Nome: Victor Cardozo Garcia
	Tia:32068883

	Como compilar: 
	unix:
	gcc -Wall -Wextra -Werror -pedantic -march=native -O2 -std=c11 -o lcs
	gcc -Wall -Wextra -Werror -pedantic -march=native -O2 -std=c11 -o lcs.exe
	
	para rodar(Unix)
	./lcs
	para rodar (Windows)
	./lcs.exe 
	Ou use o Makefile (Unix apenas)


*/
#include"../include/ep_1.h"
#define N 1000
#define T int 



// function: error
// arg: *stream, char *message
// output the error message and exit with code 1  
// return: none
inline void error(FILE *stream,const char *message)
{
	fprintf(stream,"%s\n",message);
	exit(1);
}
// function: usage
// arg: *stream, char *program_name
// output the usage of the program and exit with code 2
// return none
inline void usage(FILE *stream,const char *program_name)
{
	fprintf(stream,"Usage: %s [string1] [string2]\n",program_name);
	exit(2);
}
// function allocate_str
// arg: len
// allocates the string (char *)
// return: result_str.str 
char * allocate_str(size_t len)
{
	String result_str;
	if(len == 0)
	{
		fprintf(stderr,"[Warn] - Empty string allocation\n");
		return NULL;
	}
	if(!(result_str.str = (char *) malloc(sizeof(char) * len)))
	{
		error(stderr,"[Error] - malloc failed\n");
	}
	return result_str.str;
}
//function malloc_2d
//arg: row, col
//Allocates a 2d array (matrix) of type T
//return: Matrix_t  

#define T int
Matrix_t  malloc_2d(size_t row,size_t col)
{
	Matrix_t m;
	size_t i = 0;
	m.row = row;
	m.column = col;
	if(row == 0 || col == 0)
	{
		fprintf(stderr,"[Warning] - Allocating empty matrix (NULL) \n");
		m.matrix = NULL;
		return m;
	}

	m.matrix = (T **) malloc(row * sizeof(T *));
	if(m.matrix == NULL)
	{
		error(stderr,"[Error] - malloc() failed\n");
	}
	for(;i<row;i++)
	{
		m.matrix[i] = (T *) malloc(col * sizeof(T));
		if(m.matrix[i] == NULL)
		{
			for(size_t j = 0;j<i;j++)
			{
				free(m.matrix[j]);
			}
			free(m.matrix);
			m.matrix = NULL;
			break;
		}

	}
	return m;
}
//function free_matrix
//arg: m(matrix), col
//Frees the Matrix (2d array)
//return: none

void free_matrix(Matrix_t m,size_t col)
{
	if(m.matrix == NULL)
	{
		fprintf(stderr,"[Warning] - Matrix is NULL\n");
	}
	
	
	for(size_t i = 0;i<col;i++)
	{
		free(m.matrix[i]);
	}
	free(m.matrix);
}
// function fill_lcstable_with_zeroes
// arg: m(matrix), row, col
// zeroes the first column and first row
// return: none
void fill_lcstable_with_zeroes(Matrix_t m,size_t row ,size_t col)
{
	for(size_t i = 0;i<row;i++)
	{
		m.matrix[i][0] = 0;	
	}
	for(size_t j = 0;j<col;j++)
	{
		m.matrix[0][j] = 0;
	}
}

// function: calculate_lcs
// arg: lcs_
// calculates the lcs (Longest common substring)"
// return: lcs_t
Lcs_t calculate_lcs(Lcs_t lcs)
{
	lcs.str1.len = strlen(lcs.str1.str);
	lcs.str2.len = strlen(lcs.str2.str);
	size_t len_1 = lcs.str1.len;
	size_t len_2 = lcs.str1.len;
	lcs.m = malloc_2d(N, N);
	if(lcs.m.matrix == NULL)
	{
		error(stderr,"Matrix allocation failed\n");
	}
	if(lcs.str1.len > N && lcs.str2.len > N)
	{
		error(stderr,"[Error] - string must be at maximum 1000 characters");
	}
	size_t i = 0;
	size_t j = 0;
	fill_lcstable_with_zeroes(lcs.m, len_1 , len_2);
	lcs.lcs_result.str = NULL;
	// Construindo a matrix de baixo para cima 
	for(i = 1;i<=len_1;i++)
	{
		for(j = 1;j<=len_2;j++)
		{
			if(lcs.str1.str[i-1] == lcs.str2.str[j-1])
			{
				lcs.m.matrix[i][j] = lcs.m.matrix[i-1][j-1] + 1;
			}
			else if( lcs.m.matrix[i - 1][j] >= lcs.m.matrix[i][j-1])
			{
				lcs.m.matrix[i][j] = lcs.m.matrix[i -1][j];
			}
			else
			{
				lcs.m.matrix[i][j] = lcs.m.matrix[i][j-1];
			}
		}
	}
	i = len_1, j = len_2;
	size_t index = lcs.m.matrix[len_1][len_2];
	if(index == 0)
	{
		error(stderr,"No common substring was found\n");
	}
	lcs.lcs_result.str = (char *) allocate_str(index +  1);
	lcs.lcs_result.str [index] = '\0';
	 while(i > 0 && j > 0)
	{
		if(lcs.str1.str [ i - 1 ] == lcs.str2.str [j-1])
		{
			lcs.lcs_result.str[index-1] = lcs.str1.str [i-1];
			i--;
			j--;
			index--;
		}
		else if(lcs.m.matrix[i-1][j] > lcs.m.matrix[i][j-1])
		{
			i--;
		}
		else
		{
			j--;
		}
	}
	 return lcs;
}
// function: calculate_lcs_ptr
// arg: **lcs
// calculates the LCS (Longest common substring)
// return: none

void calculate_lcs_ptr(Lcs_t **lcs)
{
	(*lcs)->str1.len = strlen((*lcs)->str1.str);	
	(*lcs)->str2.len = strlen((*lcs)->str2.str);
	(*lcs)->m = malloc_2d(N, N);
	size_t len_1 = (*lcs)->str1.len;
	size_t len_2 = (*lcs)->str2.len;
	size_t i = 0;
	size_t j = 0;
	fill_lcstable_with_zeroes((*lcs)->m, (*lcs)->str1.len, (*lcs)->str2.len);
	(*lcs)->lcs_result.str = NULL;
	// Construindo a matrix de baixo para cima 
	for(i = 1;i<=len_1;i++)
	{
		for(j = 1;j<=len_2;j++)
		{
			if((*lcs)->str1.str [i-1] == (*lcs)->str2.str [j-1])
			{
				(*lcs)->m.matrix[i][j] = (*lcs)->m.matrix[i-1][j-1] + 1;
			}
			else if( (*lcs)->m.matrix[i - 1][j] >= (*lcs)->m.matrix[i][j-1])
			{
				(*lcs)->m.matrix[i][j] = (*lcs)->m.matrix[i -1][j];
			}
			else
			{
				(*lcs)->m.matrix[i][j] = (*lcs)->m.matrix[i][j-1];
			}
		}
	}
	i = len_1 , j = len_2;
	size_t index = (*lcs)->m.matrix[i][j];
	if(index == 0)
	{
		error(stderr,"No common substring was found\n");
	}
	(*lcs)->lcs_result.str = (char *) allocate_str(index + 1);
	(*lcs)->lcs_result.str [index] = '\0';
	 while(i > 0 && j > 0)
	{
		if((*lcs)->str1.str [ i - 1 ] == (*lcs)->str2.str[j-1])
		{
			(*lcs)->lcs_result.str[index-1] = (*lcs)->str1.str[i-1];
			i--;
			j--;
			index--;
		}
		else if((*lcs)->m.matrix[i-1][j] > (*lcs)->m.matrix[i][j-1])
		{
			i--;
		}
		else
		{
			j--;
		}
	}
		
}
// function: free_str 
// arg: String s
// Frees a string s
// return none
void free_string(String s)
{
	if(s.str == NULL)
	{
		fprintf(stderr,"[Warning] - data  pointer is NULL\n");
		return;
	}
	free(s.str);
}
int main(int argc, const char ** argv)
{
	Lcs_t lcs;
	Lcs_t *lcs_ptr = NULL;
	lcs_ptr = malloc(sizeof(Lcs_t));
	if(lcs_ptr == NULL)
	{
		error(stderr,"[Error] - malloc failed\n");
	}
	if(argc != 3 )
	{
		fprintf(stderr,"Expected 3 arguments, got %d\n",argc);
		usage(stderr,argv[0]);	
	}
	size_t size_1 = strlen(argv[1]);
	size_t size_2 = strlen(argv[2]);
	lcs.str1.str = (char *) allocate_str(size_1 + 1);
	lcs.str2.str = (char *) allocate_str(size_2 + 1);
	lcs_ptr->str1.str = (char *) allocate_str(size_1 + 1);
	lcs_ptr->str2.str = (char *) allocate_str(size_2 + 1);
	memcpy(lcs.str1.str,argv[1],size_1 + 1);
	memcpy(lcs.str2.str,argv[2],size_2 + 1);
	memcpy(lcs_ptr->str1.str,argv[1],size_1 + 1);
	memcpy(lcs_ptr->str2.str,argv[2],size_2 + 1);
	//lcs.str1[size_1] = '\0';
	//lcs.str2[size_2] = '\0';
	//lcs_ptr->str1[size_1] = '\0';
	//lcs_ptr->str2[size_2] = '\0';
	fprintf(stdout,"string_1 = %s\n",lcs.str1.str);
	fprintf(stdout,"string_2 = %s\n",lcs.str2.str);
	lcs = calculate_lcs(lcs);
	calculate_lcs_ptr(&lcs_ptr);
	fprintf(stdout,"lcs is = %s\n",lcs.lcs_result.str);
	fprintf(stdout,"lcs is = %s\n",lcs_ptr->lcs_result.str);
	fprintf(stdout,"Lenght of lcs is %zu\n",strlen(lcs.lcs_result.str));
	fprintf(stdout,"Lenght of lcs is %zu\n",strlen(lcs_ptr->lcs_result.str));
	free_matrix(lcs.m, N);
	free_matrix(lcs_ptr->m,N);
	free_string(lcs.str1);
	free_string(lcs.str2);
	free_string(lcs_ptr->str1);
	free_string(lcs_ptr->str2);
	free(lcs_ptr);
	
}
