static int init_config_log(apr_pool_t *pc, apr_pool_t *p, apr_pool_t *pt, server_rec *s)
{
    int res;

    /* First init the buffered logs array, which is needed when opening the logs. */
    if (buffered_logs) {
        all_buffered_logs = apr_array_make(p, 5, sizeof(buffered_log *));
    }

    /* Next, do "physical" server, which gets default log fd and format
     * for the virtual servers, if they don't override...
     */
    res = open_multi_logs(s, p);

    /* Then, virtual servers */

    for (s = s->next; (res == OK) && s; s = s->next) {
        res = open_multi_logs(s, p);
    }

    return res;
}