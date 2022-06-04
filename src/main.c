#include"../include/ep_1.h"
/*
 * EP 1 - LCS DNA 
 * 
 * Nome: Victor Seixas Locateli
 * TIA: 41924983
 *
 * Rodrigo Rodrigues dos Santos Rios 
 * TIA: 41783174
 * 
 * Carla Pollastrini
 * TIA: 32085877
 *
 * Nome: Victor Cardozo Garcia
 * TIA: 32068883
 * 
 * -------------------------------
 *
 * Para compílar, digite make 
 * Compilador usado: gcc
 * Sistema operacional usado: Debian GNU/Linux
 *
 *
*/ 
#define N 1000
#define T int 
inline void error(FILE *stream,const char *message)
{
	fprintf(stream,"%s\n",message);
	exit(1);
}
inline void usage(FILE *stream,const char *program_name)
{
	fprintf(stream,"Usage: %s [string1] [string2]\n",program_name);
	exit(2);
}
char * allocate_str(size_t len)
{
	String result_str;
	if(!(result_str.str = (char *) malloc(sizeof(char) * len)))
	{
		error(stderr,"[Error] - malloc failed\n");
	}
	return result_str.str;
}
#define T int
T ** malloc_2d(size_t row,size_t col)
{
	size_t i = 0;
	T **matrix = (T **) malloc(row * sizeof(T *));
	if(matrix == NULL)
	{
		error(stderr,"[Error] - malloc() failed\n");
	}
	for(;i<row;i++)
	{
		matrix[i] = (T *) malloc(col * sizeof(T));
		if(matrix[i] == NULL)
		{
			for(size_t j = 0;j<i;j++)
			{
				free(matrix[j]);
			}
			free(matrix);
			matrix = NULL;
			break;
		}

	}
	return matrix;
}
void free_matrix(T **matrix,size_t col)
{
	assert(matrix != NULL);
	for(size_t i = 0;i<col;i++)
	{
		free(matrix[i]);
	}
	free(matrix);
}
void fill_lcstable_with_zeroes(T **LCS_table,size_t row ,size_t col)
{
	for(size_t i = 0;i<=row;i++)
	{
		LCS_table[i][0] = 0;	
	}
	for(size_t j = 0;j<col;j++)
	{
		LCS_table[0][j] = 0;
	}
}

lcs_t calculate_lcs(lcs_t lcs)
{
	size_t len_1 = strlen(lcs.str1);
	size_t len_2 = strlen(lcs.str2);
	lcs.matrix = malloc_2d(N, N);
	if(lcs.matrix == NULL)
	{
		error(stderr,"Matrix allocation failed\n");
	}
	size_t i = 0;
	size_t j = 0;
	fill_lcstable_with_zeroes(lcs.matrix, len_1, len_2);
	lcs.lcs_result= NULL;
	// Construindo a matrix de baixo para cima 
	for(i = 1;i<=len_1;i++)
	{
		for(j = 1;j<=len_2;j++)
		{
			if(lcs.str1[i-1] == lcs.str2[j-1])
			{
				lcs.matrix[i][j] = lcs.matrix[i-1][j-1] + 1;
			}
			else if( lcs.matrix[i - 1][j] >= lcs.matrix[i][j-1])
			{
				lcs.matrix[i][j] = lcs.matrix[i -1][j];
			}
			else
			{
				lcs.matrix[i][j] = lcs.matrix[i][j-1];
			}
		}
	}
	i = len_1, j = len_2;
	size_t index = lcs.matrix[len_1][len_2];
	if(index == 0)
	{
		error(stderr,"No common substring was found\n");
	}
	lcs.lcs_result = (char *) allocate_str(index +  1);
	lcs.lcs_result [index-1] = '\0';
	 while(i > 0 && j > 0)
	{
		if(lcs.str1 [ i - 1 ] == lcs.str2[j-1])
		{
			lcs.lcs_result[index-1] = lcs.str1[i-1];
			i--;
			j--;
			index--;
		}
		else if(lcs.matrix[i-1][j] > lcs.matrix[i][j-1])
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
void calculate_lcs_ptr(lcs_t **lcs)
{
	size_t len_1 = strlen((*lcs)->str1);
	size_t len_2 = strlen((*lcs)->str2);
	(*lcs)->matrix = malloc_2d(N, N);
	size_t i = 0;
	size_t j = 0;
	fill_lcstable_with_zeroes((*lcs)->matrix, len_1, len_2);
	(*lcs)->lcs_result= NULL;
	// Construindo a matrix de baixo para cima 
	for(i = 1;i<=len_1;i++)
	{
		for(j = 1;j<=len_2;j++)
		{
			if((*lcs)->str1[i-1] == (*lcs)->str2[j-1])
			{
				(*lcs)->matrix[i][j] = (*lcs)->matrix[i-1][j-1] + 1;
			}
			else if( (*lcs)->matrix[i - 1][j] >= (*lcs)->matrix[i][j-1])
			{
				(*lcs)->matrix[i][j] = (*lcs)->matrix[i -1][j];
			}
			else
			{
				(*lcs)->matrix[i][j] = (*lcs)->matrix[i][j-1];
			}
		}
	}
	i = len_1, j = len_2;
	size_t index = (*lcs)->matrix[len_1][len_2];
	if(index == 0)
	{
		error(stderr,"No common substring was found\n");
	}
	(*lcs)->lcs_result = (char *) allocate_str(index + 1);
	(*lcs)->lcs_result [index - 1] = '\0';
	 while(i > 0 && j > 0)
	{
		if((*lcs)->str1 [ i - 1 ] == (*lcs)->str2[j-1])
		{
			(*lcs)->lcs_result[index-1] = (*lcs)->str1[i-1];
			i--;
			j--;
			index--;
		}
		else if((*lcs)->matrix[i-1][j] > (*lcs)->matrix[i][j-1])
		{
			i--;
		}
		else
		{
			j--;
		}
	}
		
}
int main(int argc, const char ** argv)
{
	lcs_t lcs;
	lcs_t *lcs_ptr = NULL;
	lcs_ptr = malloc(sizeof(lcs_t));
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
	lcs.str1 = (char *) allocate_str(size_1 + 1);
	lcs.str2 = (char *) allocate_str(size_2 + 1);
	lcs_ptr->str1 = (char *) allocate_str(size_1);
	lcs_ptr->str2 = (char *) allocate_str(size_2);
	memcpy(lcs.str1,argv[1],size_1);
	memcpy(lcs.str2,argv[2],size_2);
	memcpy(lcs_ptr->str1,argv[1],size_1);
	memcpy(lcs_ptr->str2,argv[2],size_2);
	lcs.str1[size_1 - 1] = '\0';
	lcs.str2[size_2 - 1] = '\0';
	lcs_ptr->str1[size_1-1] = '\0';
	lcs_ptr->str2[size_2 - 1] = '\0';
	fprintf(stdout,"string_1 = %s\n",lcs.str1);
	fprintf(stdout,"string_2 = %s\n",lcs.str2);
	lcs = calculate_lcs(lcs);
	calculate_lcs_ptr(&lcs_ptr);
	fprintf(stdout,"lcs is = %s\n",lcs.lcs_result);
	fprintf(stdout,"lcs is = %s\n",lcs_ptr->lcs_result);
	free_matrix(lcs.matrix, N);
	free_matrix(lcs_ptr->matrix,N);
	free(lcs.str1);
	free(lcs.str2);
	free(lcs_ptr->str1);
	free(lcs_ptr->str2);

	
}
