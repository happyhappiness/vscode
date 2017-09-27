
/* shared by service.c as global, although
 * perhaps it should be private.
 */
apr_pool_t *pconf;

/* definitions from child.c */
void child_main(apr_pool_t *pconf);

/* Only one of these, the pipe from our parent, meant only for
 * one child worker's consumption (not to be inherited!)
 * XXX: decorate this name for the trunk branch, was left simplified
 *      only to make the 2.2 patch trivial to read.
 */
static HANDLE pipe;

/* Stub functions until this MPM supports the connection status API */

AP_DECLARE(void) ap_update_connection_status(long conn_id, const char *key, \
                                             const char *value)
{
    /* NOP */
}

AP_DECLARE(void) ap_reset_connection_status(long conn_id)
{
    /* NOP */
}

AP_DECLARE(apr_array_header_t *) ap_get_status_table(apr_pool_t *p)
{
    /* NOP */
    return NULL;
}

/*
 * Command processors
 */

static const char *set_threads_per_child (cmd_parms *cmd, void *dummy, char *arg)
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }

    ap_threads_per_child = atoi(arg);
    return NULL;
}
static const char *set_thread_limit (cmd_parms *cmd, void *dummy, const char *arg)
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }

    thread_limit = atoi(arg);
    return NULL;
}

static const command_rec winnt_cmds[] = {
LISTEN_COMMANDS,
AP_INIT_TAKE1("ThreadsPerChild", set_threads_per_child, NULL, RSRC_CONF,
  "Number of threads each child creates" ),
AP_INIT_TAKE1("ThreadLimit", set_thread_limit, NULL, RSRC_CONF,
  "Maximum worker threads in a server for this run of Apache"),
{ NULL }
};


/*
 * Signalling Apache on NT.
