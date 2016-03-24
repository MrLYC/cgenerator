#include <stdbool.h>
#include <stddef.h>

#ifndef CGENERATOR
#define CGENERATOR

typedef struct {
    void * position;
    bool finished;
    bool started;
    bool yielded;
} GenState;

#define Gen_Init(gen_state) gen_init(&(gen_state));

#define Gen_Begin(gen_state) \
GenState * _gen_state_ = &(gen_state); \
if (_gen_state_->finished) { _gen_state_->yielded = true; goto _Gen_Finished; }  \
else if (_gen_state_->started) { _gen_state_->yielded = true; goto *(_gen_state_->position); } \
else { _gen_state_->started = true; _gen_state_->yielded = false; }

#define Gen_Yield(gen_value, ...) \
_Gen##__VA_ARGS__: if (!(_gen_state_->yielded)) { _gen_state_->position = &&_Gen##__VA_ARGS__; return gen_value; } \
else { _gen_state_->yielded = false; }


#define Gen_Return(gen_value) \
gen_finish(_gen_state_); \
_Gen_Finished: _gen_state_->position = &&_Gen_Finished; \
return gen_value;

void gen_init(GenState *);
void gen_finish(GenState *);


#endif
