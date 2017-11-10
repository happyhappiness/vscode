static apr_status_t default_build_command(const char **cmd, const char ***argv,
                                          request_rec *r, apr_pool_t *p,
                                          cgi_exec_info_t *e_info)
{
    int numwords, x, idx;
    char *w;
    const char *args = NULL;

    if (e_info->process_cgi) {
        *cmd = r->filename;
        /* Do not process r->args if they contain an '=' assignment
         */
        if (r->args && r->args[0] && !ap_strchr_c(r->args, '=')) {
            args = r->args;
        }
    }

    if (!args) {
        numwords = 1;
    }
    else {
        /* count the number of keywords */
        for (x = 0, numwords = 2; args[x]; x++) {
            if (args[x] == '+') {
                ++numwords;
            }
        }
    }
    /* Everything is - 1 to account for the first parameter
     * which is the program name.
     */
    if (numwords > APACHE_ARG_MAX - 1) {
        numwords = APACHE_ARG_MAX - 1;    /* Truncate args to prevent overrun */
    }
    *argv = apr_palloc(p, (numwords + 2) * sizeof(char *));
    (*argv)[0] = *cmd;
    for (x = 1, idx = 1; x < numwords; x++) {
        w = ap_getword_nulls(p, &args, '+');
        ap_unescape_url(w);
        (*argv)[idx++] = ap_escape_shell_cmd(p, w);
    }
    (*argv)[idx] = NULL;

    return APR_SUCCESS;
}