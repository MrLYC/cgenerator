#include <stdbool.h>
#include <stddef.h>

typedef struct {
    void * position;
    bool finished;
    bool started;
    bool yielded;
} GenState;

#ifndef Gen_Label
#define Gen_Label(name) _Gen##name
#endif

#ifndef Gen_End_Label
#define Gen_End_Label Gen_Label(_Finished_)
#endif

#ifndef Gen_Init
#define Gen_Init(gen_state) gen_init(&(gen_state));
#endif

#ifndef Gen_Begin
#define Gen_Begin(gen_state) \
GenState * _gen_state_ = &(gen_state); \
if (_gen_state_->finished) { \
    _gen_state_->yielded = true; \
    goto Gen_End_Label; \
}  \
else if (_gen_state_->started) { \
    _gen_state_->yielded = true; \
    goto *(_gen_state_->position); \
} \
else { \
    _gen_state_->started = true; \
    _gen_state_->yielded = false; \
}
#endif

#ifndef Gen_Yield
#define Gen_Yield(gen_value, ...) \
Gen_Label(__VA_ARGS__): if (_gen_state_->yielded) { \
    _gen_state_->yielded = false; \
} \
else { \
    _gen_state_->position = &&Gen_Label(__VA_ARGS__); \
    return gen_value; \
}
#endif

#ifndef Gen_Return
#define Gen_Return(gen_value) \
gen_finish(_gen_state_); \
Gen_End_Label: _gen_state_->position = &&Gen_End_Label; \
return gen_value;
#endif

void gen_init(GenState *);
void gen_finish(GenState *);
