static void *xcalloc(size_t num, size_t size)
{
    void *ret = calloc(num, size);
    if (ret == NULL) {
        fprintf(stderr, "Could not allocate memory (%"
                APR_SIZE_T_FMT" bytes)\n", size*num);
        exit(1);
    }
    return ret;
}