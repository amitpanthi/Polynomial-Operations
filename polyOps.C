#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct poly {
    int e;          /*Exponent*/
    int c;          /*Coefficient*/
    poly* next;
}poly;

poly* make_poly(int degree); 
void printPoly(poly *);

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
    int choice = 0;
    int degree1, degree2;
    
    printf("------------------POLYNOMIAL OPERATIONS------------------\n");
   
    //Input
    printf("Please enter input for both polynomials\n");
    printf("Please enter the degree of polynomial number 1\n");
    scanf("%d", &degree1);
    poly *poly1_p = NULL;
    poly1_p = (poly*)malloc(sizeof(poly));
    poly1_p = make_poly(degree1); 

    printf("Please enter the degree of polynomial number 2\n");
    scanf("%d", &degree2);
    poly *poly2_p = NULL;
    poly2_p = (poly*)malloc(sizeof(poly));
    poly2_p = make_poly(degree2);

    //Initializing a null poly term to hold the operation value
    poly *poly_op = NULL;
    poly_op = (poly*)malloc(sizeof(poly));


    //Menu block
    do
    {
        printf("\nPlease select an appropriate choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
            //Addition block
            poly_op = polyAdd(poly1_p, poly2_p);
            printf("(");
            printPoly(poly1_p);
            printf(") + (");
            printPoly(poly2_p);
            printf(") = ");
            printPoly(poly_op);
            break;

            case 2:
            //Multiplication block
            poly_op = polyMultiply(poly1_p, poly2_p);
            printf("(");
            printPoly(poly1_p);
            printf(") * (");
            printPoly(poly2_p);
            printf(") = ");
            printPoly(poly_op);
            break;

            case 3:
            //Differentiation block
            poly_op = polyDif(poly1_p);
            printf("d/dx(");
            printPoly(poly1_p);
            printf(") = ");
            printPoly(poly_op);
            printf("\n");
            
            poly_op = polyDif(poly2_p);
            printf("d/dx(");
            printPoly(poly2_p);
            printf(") = ");
            printPoly(poly_op);

            break;
        }
    } while (choice != 5);

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

poly* polyMultiply(poly *p1,poly *p2)
{   
    poly* start;
    poly* previous;
    int limit = (p1->e)+(p2->e);
    for(int i=0;i<limit+1;i++)
    {
        if(i==0){
            poly* term = NULL;
            term = (poly*)malloc(sizeof(poly));

            term->e=limit-i;
            term->c=0;
            term->next=NULL;

            start=term;
            previous=term;
        }

        else{

            poly* term = NULL;
            term = (poly*)malloc(sizeof(poly));

            term->e=limit-i;
            term->c=0;
            term->next=NULL;

            previous->next=term;
            previous=term;
            
        
        }
    }
    poly *temp=p2;

    while(p1!=NULL)
    {
        poly* term = start;

        p2=temp;
        while(p2!=NULL)
        {
            poly* term = start;
            while((term->e)!=(p1->e)+(p2->e))
            {
                term=term->next;

            }
            if(term->e==(p1->e)+(p2->e))
            {
                term->c=term->c+(p1->c)*(p2->c);
            }
        
        p2=p2->next;
        }

        p1=p1->next;
    }

    return start;
} 

poly* polyAdd(poly *p1,poly *p2)
{   
    
    poly* greater;
    poly* smaller;
    poly* start;
    poly* previous;


    if((p1->e)>(p2->e))  //the greater poly is assigned as greater 
    {
        greater=p1;
        smaller=p2;
    }
    else
    {
        greater=p2;
        smaller=p1;
    }
    int limit = smaller->e;
    int i=0;
    while(smaller!=NULL)
    {
        // first we have to set start=the first term
        if(i==0)
        {
            i++;
            poly* term = NULL;
            term = (poly*)malloc(sizeof(poly));
            
            term->e=greater->e;
            term->c=greater->c;
            start=term;
            term->next=NULL;
            previous=term;
        
        //as we have set the first term of poly = to the 1st term of greater, greater= greater-> next for rest of the polynomials
            if((greater->e)==(smaller->e))
            {   
                term->c=((greater->c)+(smaller->c));
                smaller=smaller->next;
            }
            greater=greater->next;
           
        }
        //we are setting the terms of added polynomial=greater polynomial till the power of grater polynomial becomes equal to the power of lower polynomial
        
        while((greater->e)!=(smaller->e))
        {   
            
            poly* term = NULL;
            term = (poly*)malloc(sizeof(poly));
            term->e=greater->e;
            term->c=greater->c;
            term->next=NULL;
            previous->next=term;
            greater=greater->next;
            previous=term;
            
        }
        
        //after the while loop greater polynomial's power will be equal to smaller polynomial's power
        // so we add the coefficient
        
        poly* term = NULL;
        term = (poly*)malloc(sizeof(poly));
        term->e=greater->e;
        term->c=((greater->c)+(smaller->c));
        term->next=NULL;
        previous->next=term;
        greater=greater->next;
        smaller=smaller->next;
        previous=term;   
    }

    return start;
}    
