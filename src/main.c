#include <stdio.h>
#include "gen.h"


typedef struct context_t {
    GenState state;
    int value;
    int end;
} Context;


int range(Context * c_ptr) {
    printf("ready\n");
    Gen_Begin(c_ptr->state);
    printf("begin\n");
    while (c_ptr->value < c_ptr->end) {
        Gen_Yield(c_ptr->value);
        c_ptr->value += 1;
    }
    while (c_ptr->value >= 0) {
        Gen_Yield(c_ptr->value, desc);
        c_ptr->value -= 1;
    }
    Gen_Return(-2);
}


int main(int argc, char const *argv[]) {
    Context context;
    context.value = 0;
    context.end = 5;

    Gen_Init(context.state);
    int i;
    while ((i = range(&context)) >= 0) {
        printf("%d\n", i);
    }
    printf("%d\n", range(&context));

    return 0;
}
