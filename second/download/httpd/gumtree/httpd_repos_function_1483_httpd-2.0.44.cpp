static char *header_file(apr_pool_t *p, int dirlevels, int dirlength, 
                         const char *root, const char *name)
{
    char *hashfile;
    hashfile = generate_name(p, dirlevels, dirlength, name);
    return apr_pstrcat(p, root, "/", hashfile, CACHE_HEADER_SUFFIX, NULL);
}