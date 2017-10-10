#include "dir.h"
#include "utf8.h"
#include "submodule.h"
#include "submodule-config.h"
#include "string-list.h"
#include "run-command.h"

struct module_list {
	const struct cache_entry **entries;
	int alloc, nr;
};
#define MODULE_LIST_INIT { NULL, 0, 0 }
