const char *
strnrchr(const char *s, size_t count, int c)
{
    const char *rv=NULL;
    const char *l=s;
    while (count > 0 && *l != 0) {
        if (*l==c)
            rv=l;
        ++l;
        --count;
    }
    return rv;
}