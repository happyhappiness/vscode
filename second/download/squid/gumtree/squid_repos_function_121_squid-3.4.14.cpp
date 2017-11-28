void
my_free(char *file, int line, void *ptr)
{
#if 0
    fprintf(stderr, "{%s:%d:%p", file, line, ptr);
#endif
    free(ptr);
#if 0
    fprintf(stderr, "}\n");
#endif
}