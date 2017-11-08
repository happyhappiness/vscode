static char *next_substitution(const char *buf,
                               const apr_array_header_t * args, int *whichone)
{
    char *chosen = NULL, **tab = (char **) args->elts;
    size_t lchosen = 0;
    int i;

    for (i = 0; i < args->nelts; i++) {
        char *found = ap_strstr((char *) buf, tab[i]);
        size_t lfound = strlen(tab[i]);
        if (found && (!chosen || found < chosen ||
                      (found == chosen && lchosen < lfound))) {
            chosen = found;
            lchosen = lfound;
            *whichone = i;
        }
    }

    return chosen;
}