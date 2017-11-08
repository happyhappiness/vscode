static const char *add_index(cmd_parms *cmd, void *dummy, const char *arg)
{
    dir_config_rec *d = dummy;
    const char *t, *w;
    int count = 0;

    if (!d->index_names) {
        d->index_names = apr_array_make(cmd->pool, 2, sizeof(char *));
    }

    t = arg;
    while ((w = ap_getword_conf(cmd->pool, &t)) && w[0]) {
        if (count == 0 && !strcasecmp(w, "disabled")) {
            /* peek to see if "disabled" is first in a series of arguments */
            const char *tt = t;
            const char *ww = ap_getword_conf(cmd->temp_pool, &tt);
            if (ww == NULL || !ww[0]) {
               /* "disabled" is first, and alone */
               apr_array_clear(d->index_names); 
               break;
            }
        }
        *(const char **)apr_array_push(d->index_names) = w;
        count++;
    }

    return NULL;
}