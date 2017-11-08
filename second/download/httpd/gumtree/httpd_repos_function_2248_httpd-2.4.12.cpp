static void grow_buffer(apr_pool_t *pool, char **buffer,
                        char **spend, unsigned int *cursize,
                        unsigned int newsize)
{
    char* newbuffer = NULL;
    int spendsize = 0;
    if (*cursize >= newsize)
        return;
    /* Avoid number of times realloc is called. It could cause huge memory
     * requirement if line size is huge e.g 2 MB */
    if (newsize < *cursize * 2) {
        newsize = *cursize * 2;
    }

    /* Align it to 4 KB boundary */
    newsize = (newsize  + ((1 << 12) - 1)) & ~((1 << 12) -1);
    newbuffer = apr_pcalloc(pool, newsize);
    if (*spend && *buffer && (*cursize > 0)) {
        spendsize = *spend - *buffer;
    }
    if ((*cursize > 0) && *buffer) {
        memcpy(newbuffer, *buffer, *cursize);
    }
    *buffer = newbuffer;
    *cursize = newsize;
    if (spend != buffer) {
        *spend = *buffer + spendsize;
    }
}