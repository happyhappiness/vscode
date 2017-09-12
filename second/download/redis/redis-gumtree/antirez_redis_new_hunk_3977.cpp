 * around when there is a child performing saving operations. */
static int dict_can_resize = 1;

/* -------------------------- private prototypes ---------------------------- */

static int _dictExpandIfNeeded(dict *ht);
