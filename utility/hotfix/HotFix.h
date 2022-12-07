#ifndef HOT_FIX_H
#define HOT_FIX_H

using FIXTABLE = struct {
	void* new_func;
	void* old_func;
};

int fix_func(const void* new_func, void* old_func);

int do_fix(const char* patch);

#endif //HOT_FIX_H
