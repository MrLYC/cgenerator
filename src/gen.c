#include "gen.h"

void gen_init(GenState * state_ptr) {
    state_ptr->position = NULL;
    state_ptr->finished = false;
    state_ptr->started = false;
}

void gen_finish(GenState * state_ptr) {
    state_ptr->finished = true;
}
