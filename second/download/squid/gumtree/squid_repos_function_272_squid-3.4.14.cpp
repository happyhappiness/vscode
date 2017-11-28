char *
utf8dup(struct main_args *margs)
{
    size_t c = 0;
    unsigned char s;
    size_t n;
    char *src;
    unsigned char *p, *dupp;

    src = margs->glist;
    if (!src)
        return NULL;
    for (n = 0; n < strlen(src); ++n)
        if ((unsigned char) src[n] > 127)
            ++c;
    if (c != 0) {
        p = (unsigned char *) xmalloc(strlen(src) + c);
        dupp = p;
        for (n = 0; n < strlen(src); ++n) {
            s = (unsigned char) src[n];
            if (s > 127 && s < 192) {
                *p = 194;
                ++p;
                *p = s;
            } else if (s > 191) {
                *p = 195;
                ++p;
                *p = s - 64;
            } else
                *p = s;
            ++p;
        }
        *p = '\0';
        debug((char *) "%s| %s: INFO: Group %s as UTF-8: %s\n", LogTime(), PROGRAM, src, dupp);
        return (char *) dupp;
    } else
        return xstrdup(src);
}