static inline char *
xstrdup(const char *s)
{
    size_t memsize = strlen(s) + 1;
    char *ptr = malloc(memsize);
    if (!ptr) {
	fprintf(stderr, "virtual memory exhausted.\n");
	exit(EXIT_FAILURE);
    }
    strlcpy(ptr, s, memsize);
    return ptr;
}