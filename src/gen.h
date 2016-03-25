#include <stdbool.h>
#include <stddef.h>

typedef struct {
    void * position;
    bool finished;
    bool started;
} GenState;

#ifndef Gen_Label
#define Gen_Label(name) _Gen_##name
#endif

#ifndef Gen_Mark
#define Gen_Mark(label) label: _gen_state_->position = &&label;
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
    goto Gen_End_Label; \
}  \
else if (_gen_state_->started) { \
    goto *(_gen_state_->position); \
} \
else { \
    _gen_state_->position = &&Gen_End_Label; \
    _gen_state_->started = true; \
}
#endif

#ifndef Gen_Yield
#define Gen_Yield(gen_value, ...) \
_gen_state_->position = &&Gen_Label(__VA_ARGS__); \
return gen_value; \
Gen_Mark(Gen_Label(__VA_ARGS__));
#endif

#ifndef Gen_Finish
#define Gen_Finish(...) \
gen_finish(_gen_state_); \
Gen_Mark(Gen_End_Label); \
return __VA_ARGS__;
#endif

void gen_init(GenState *);
void gen_finish(GenState *);
