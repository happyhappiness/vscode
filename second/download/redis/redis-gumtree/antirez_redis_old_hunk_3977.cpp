 * around when there is a child performing saving operations. */
static int dict_can_resize = 1;

/* ---------------------------- Utility funcitons --------------------------- */

static void _dictPanic(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    fprintf(stderr, "\nDICT LIBRARY PANIC: ");
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n\n");
    va_end(ap);
}

/* ------------------------- Heap Management Wrappers------------------------ */

static void *_dictAlloc(size_t size)
{
    void *p = zmalloc(size);
    if (p == NULL)
        _dictPanic("Out of memory");
    return p;
}

static void _dictFree(void *ptr) {
    zfree(ptr);
}

/* -------------------------- private prototypes ---------------------------- */

static int _dictExpandIfNeeded(dict *ht);
