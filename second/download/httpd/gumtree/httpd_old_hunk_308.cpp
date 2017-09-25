    return APR_SUCCESS;
}


static int init_config_log(apr_pool_t *pc, apr_pool_t *p, apr_pool_t *pt, server_rec *s)
{
    /* First, do "physical" server, which gets default log fd and format
     * for the virtual servers, if they don't override...
     */
    int res = open_multi_logs(s, p);

    /* Then, virtual servers */

    for (s = s->next; (res == OK) && s; s = s->next) {
        res = open_multi_logs(s, p);
    }

    return res;
}

static void init_child(apr_pool_t *p, server_rec *s)
{
    /* Now register the last buffer flush with the cleanup engine */
    if (buffered_logs) {
        apr_pool_cleanup_register(p, s, flush_all_logs, flush_all_logs);
    }
}

static void ap_register_log_handler(apr_pool_t *p, char *tag, 
                                    ap_log_handler_fn_t *handler, int def)
{
