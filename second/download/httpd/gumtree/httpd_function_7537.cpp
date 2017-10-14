static void *xmalloc(size_t size)
{
    void *ret = malloc(size);
    if (ret == NULL) {
        fprintf(stderr, "Could not allocate memory (%"
                APR_SIZE_T_FMT" bytes)\n", size);
        exit(1);
    }
    return ret;
}