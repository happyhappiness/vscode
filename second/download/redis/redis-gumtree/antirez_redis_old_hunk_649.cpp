void debugCommand(client *c) {
    if (!strcasecmp(c->argv[1]->ptr,"segfault")) {
        *((char*)-1) = 'x';
    } else if (!strcasecmp(c->argv[1]->ptr,"oom")) {
        void *ptr = zmalloc(ULONG_MAX); /* Should trigger an out of memory. */
        zfree(ptr);
