static key_t our_ftok(const char *filename)
{
    /* to help avoid collisions while still using
     * an easily recreated proj_id */
    apr_ssize_t slen = strlen(filename);
    return ftok(filename,
                (int)apr_hashfunc_default(filename, &slen));
}