static const char *guess_domain(apr_pool_t *p, const char *uri,
                                const char *filename, const char *dir)
{
    apr_size_t u_len = strlen(uri), f_len = strlen(filename), 
      d_len = strlen(dir);
    const char *u, *f;


    /* Because of things like mod_alias and mod_rewrite and the fact that
     * protection is often on a directory basis (not a location basis) it
     * is hard to determine the uri to put in the domain attribute.
     *
     * What we do is the following: first we see if the directory is
     * a prefix for the uri - if this is the case we assume that therefore
     * a <Location> directive was protecting this uri and we can use it
     * for the domain.
     */
    if (u_len >= d_len && !memcmp(uri, dir, d_len)) {
        return dir;
    }

    /* Now we check for <Files ...>, and if we find one we send back a
     * dummy uri - this is the only way to specify that the protection
     * space only covers a single uri.
     */
    if (dir[0] != '/') {
        /* This doesn't work for Amaya (ok, it's of arguable validity in
         * the first place), so just return the file name instead
        return "http://0.0.0.0/";
         */
        return dir;
    }

    /* Next we find the largest common common suffix of the request-uri
     * and the final file name, ignoring any extensions; this gives us a
     * hint as to where any rewriting could've occured (assuming that some
     * prefix of the uri is rewritten, not a suffix).
     */
    u = uri + u_len - 1;        /* strip any extension */
    while (u > uri && *u != '/') {
        u--;
    }
    while (*u && *u != '.') {
        u++;
    }
    if (*u == '.') {
        u--;
    }
    if (*u == '/') {
        u--;
    }

    f = filename + f_len - 1;   /* strip any extension */
    while (f > filename && *f != '/') {
        f--;
    }
    while (*f && *f != '.') {
        f++;
    }
    if (*f == '.') {
        f--;
    }
    if (*f == '/') {
        f--;
    }

    while (*f == *u && f > filename && u > uri) {
        u--;
        f--;
    }
    f++;
    u++;

    while (*f && *f != '/') {
        f++;
        u++;  /* suffix must start with / */
    }

    /* Now, if the directory reaches into this common suffix then we can
     * take the uri with the same reach.
     */
    if ((unsigned long) (f-filename) < d_len) {
        char *tmp = apr_pstrdup(p, uri);
        tmp[(u-uri)+(d_len-(f-filename))] = '\0';
        return tmp;
    }

    return "";  /* give up */
}