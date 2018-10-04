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
poly* polyAdd(poly*, poly*); 
poly* polySub(poly*, poly*);
poly* polyMultiply(poly*, poly*);
poly* polyDif(poly*);

int main()
{
    int degree1, degree2;
    //printf("Please enter the first polynomial, starting from highest degree to lowest degree.\n");
    //printf("WARNING: Do not use ^ for the polynomial degree, just write polynomials in AxB format, where A is coefficient and B is degree\n");
    printf("Please enter the degree of polynomial number 1\n");
    scanf("%d", &degree1);    
    printf("Please enter the degree of polynomial number 2\n");
    scanf("%d", &degree2);

    poly *poly1_p = NULL;
    poly1_p = (poly*)malloc(sizeof(poly));

    poly *poly2_p = NULL;
    poly2_p = (poly*)malloc(sizeof(poly));

    poly *poly_add = NULL;
    poly_add = (poly*)malloc(sizeof(poly));

    printf("Input for first polynomial\n");
    poly1_p = make_poly(degree1);
    
    printf("Input for second polynomial\n");
    poly2_p = make_poly(degree2);

    poly_add = polyDif(poly1_p);
    //polySub(poly1_p, poly2_p);
    //polyMultiply(poly1_p, poly2_p);
    printPoly(poly_add);
    printf("\n");
    printPoly(poly2_p);

    return 0;
}

poly* make_poly(int d)
{
    int i;
    int coeff;

    poly* start = NULL;

    poly* term;
    term = (poly*)malloc(sizeof(poly));

    poly* previous;
    
    for (i = 0; i <= d; i++)
    {
        poly* term;
        term = (poly*)malloc(sizeof(poly));

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
    while(p -> next != NULL) 
    { 
        if(p -> e == 0)
        {
            printf("%d", p -> c);
            p = p -> next; 
        }
        else if(p -> c == 0)
        {
            p = p -> next;
            continue;
        }
        else
        {
        printf("%dx^%d", p -> c, p -> e); 
        p = p -> next; 
        }

        if(p -> next != NULL)
            printf(" + ");
    }

    if (p -> c == 0)
    {
        printf("");
    } 
    else 
    {
    printf(" + %d", p -> c) ;
    }
}

poly* polyDif(poly* p)
{
//
    poly* start = NULL;
    poly* ptr = NULL;

    while(p)
    {
        poly* term = NULL;
        term = (poly*)malloc(sizeof(poly));
        term -> c = (p -> c) * (p -> e);
        term -> e = (p -> e) - 1;
        term -> next = NULL;
        if(start == NULL)
        {
            start = term;
        } 
        
        else 
        {
            ptr = start;
            while(ptr -> next != NULL)
            {
                ptr = ptr -> next;
            }
            ptr -> next = term;
        }

        p = p -> next;
    }

    return start;
}
