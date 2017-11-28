char *
convert_domain_to_bind_path(char *domain)
{
    char *dp, *bindp = NULL, *bp = NULL;
    size_t i = 0;

    if (!domain)
        return NULL;

    for (dp = domain; *dp; ++dp) {
        if (*dp == '.')
            ++i;
    }
    /*
     * add dc= and
     * replace . with ,dc= => new length = old length + #dots * 3 + 3
     */
    bindp = (char *) xmalloc(strlen(domain) + 3 + i * 3 + 1);
    bp = bindp;
    strcpy(bp, "dc=");
    bp += 3;
    for (dp = domain; *dp; ++dp) {
        if (*dp == '.') {
            strcpy(bp, ",dc=");
            bp += 4;
        } else {
            *bp = *dp;
            ++bp;
        }
    }
    *bp = '\0';
    return bindp;
}