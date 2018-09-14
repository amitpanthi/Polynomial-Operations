#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct poly {
    int e;          /*Exponent*/
    int c;          /*Coefficient*/
    poly* next;
}poly;

poly* make_poly(int degree); 
void printPoly(poly *); //one of these ^ don't work for now :D
//Operations
/*
A more convenient (and useful application) would be to set the return type to poly* instead of void
so you can directly use printPoly(result_poly*). Will decide on what to do about this later
*/
void polyAdd(poly*, poly*); 
void polySub(poly*, poly*);
void polyMultiply(poly*, poly*);

int main()
{
    int degree1, degree2;
    //printf("Please enter the first polynomial, starting from highest degree to lowest degree.\n");
    //printf("WARNING: Do not use ^ for the polynomial degree, just write polynomials in AxB format, where A is coefficient and B is degree\n");
    printf("Please enter the number of terms in first polynomial (Degree + 1)\n");
    scanf("%d", &degree1);    
    printf("Please enter the number of terms in first polynomial (Degree + 1)\n");
    scanf("%d", &degree2);

    poly *poly1_p = NULL;
    poly1_p = (poly*)malloc(sizeof(poly));
    poly *poly2_p = NULL;
    poly2_p = (poly*)malloc(sizeof(poly));

    poly1_p = make_poly(degree1);
    poly2_p = make_poly(degree2);

    polyAdd(poly1_p, poly2_p);
    polySub(poly1_p, poly2_p);
    polyMultiply(poly1_p, poly2_p);
    //printPoly(poly1_p);

    return 0;
}

poly* make_poly(int d)
{
    int i;
    int coeff;

    poly* start = NULL;

    poly* term = NULL;
    term = (poly*)malloc(sizeof(poly));

    poly* previous = NULL;
    
    for (i = 0; i < d; i++)
    {

        //Take input. If iterator == final term, it is a constant
        if(i < d)
        {
            printf("Please enter the coefficient of term no. %d\n", i + 1);
            scanf("%d", &coeff);
        } else if (i == d) {
            printf("Please enter the constant term\n");
            scanf("%d", &coeff);
        }

        if(i == 0)
        {
            term -> c = coeff;
            term -> e = d - i;
            term -> next = NULL;

            start = term;

            //previous -> next = term;
            previous = term;
        }

        else
        {
            term -> c = coeff;
            term -> e = d - i;
            term -> next = NULL;

            previous -> next = term;
            previous = term;
        }
    }

    return start;
}

void printPoly(poly* p)
{
    while(p->next != NULL) 
    { 
        printf("%dx^%d", p -> c, p -> e); 
        p = p -> next; 
        if(p -> next != NULL) 
            printf(" + "); 
        } 
}