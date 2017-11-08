static int ignore_header(const literal *lits, size_t llen,
                         const char *name, size_t nlen)
{
    const literal *lit;
    int i;
    
    for (i = 0; i < llen; ++i) {
        lit = &lits[i];
        if (lit->len == nlen && !apr_strnatcasecmp(lit->name, name)) {
            return 1;
        }
    }
    return 0;
}