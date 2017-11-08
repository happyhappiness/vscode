static char *subst_prefix_path(request_rec *r, char *input, char *match,
                               const char *subst)
{
    char matchbuf[LONG_STRING_LEN];
    char substbuf[LONG_STRING_LEN];
    char *output;
    int l;

    output = input;

    /* first create a match string which always has a trailing slash */
    l = apr_cpystrn(matchbuf, match, sizeof(matchbuf)) - matchbuf;
    if (matchbuf[l-1] != '/') {
       matchbuf[l] = '/';
       matchbuf[l+1] = '\0';
       l++;
    }
    /* now compare the prefix */
    if (strncmp(input, matchbuf, l) == 0) {
        rewritelog(r, 5, "strip matching prefix: %s -> %s", output, output+l);
        output = apr_pstrdup(r->pool, output+l);

        /* and now add the base-URL as replacement prefix */
        l = apr_cpystrn(substbuf, subst, sizeof(substbuf)) - substbuf;
        if (substbuf[l-1] != '/') {
           substbuf[l] = '/';
           substbuf[l+1] = '\0';
           l++;
        }
        if (output[0] == '/') {
            rewritelog(r, 4, "add subst prefix: %s -> %s%s",
                       output, substbuf, output+1);
            output = apr_pstrcat(r->pool, substbuf, output+1, NULL);
        }
        else {
            rewritelog(r, 4, "add subst prefix: %s -> %s%s",
                       output, substbuf, output);
            output = apr_pstrcat(r->pool, substbuf, output, NULL);
        }
    }
    return output;
}