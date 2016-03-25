#include <stdio.h>
#include <stdlib.h>
#include "gen.h"

/* Output:
1   *
2   **
3   ***
4   ****
5   *****
4   ****
3   ***
2   **
1   *
state finished: 1, value: 0
*/


typedef struct context_t {
    GenState state;
    int number;
    int width;
} Context;


void print_star(int width) {
    for (int i = 0; i < width; i++) {
        printf("*");
    }
    printf("\n");
}


int triangle(Context * c_ptr) {
    Gen_Begin(c_ptr->state);  // setup generator state
    c_ptr->number = 1;

    while (c_ptr->number < c_ptr->width) {
        Gen_Yield(c_ptr->number);  // yield c_ptr->number and mark the position
        print_star(c_ptr->number);
        c_ptr->number += 1;
    }

    while (c_ptr->number > 0) {
        Gen_Yield(c_ptr->number, desc);  // desc is the position name, the first position can be empty
        print_star(c_ptr->number);
        c_ptr->number -= 1;
    }
    Gen_Return(0);  // when genrator finished, return the default value
}


int main(int argc, char const *argv[]) {
    Context context;
    context.width = 5;

    if (argc > 1) {
        context.width = atoi(argv[1]);
    }

    Gen_Init(context.state);
    int i;
    while (!context.state.finished) {
        i = triangle(&context);
        if (!context.state.finished) {
            printf("%-3d ", i);  // print star number and re-enter into the generator
        }
    }
    printf("state finished: %d, value: %d\n", context.state.finished, triangle(&context));
    return 0;
}
