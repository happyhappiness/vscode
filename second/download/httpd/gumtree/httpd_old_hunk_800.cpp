 * In other words, don't change this one without checking table_do in alloc.c.
 * It returns true unless there was a write error of some kind.
 */
static int perchild_header_field(perchild_header *h,
                             const char *fieldname, const char *fieldval)
{
    apr_pstrcat(h->p, h->headers, fieldname, ": ", fieldval, CRLF); 
    return 1;
}


static void child_main(int child_num_arg)
{
    int i;
    apr_status_t rv;

    my_pid = getpid();
    child_num = child_num_arg;
    apr_pool_create(&pchild, pconf);

    /*stuff to do before we switch id's, so we have permissions.*/

    rv = SAFE_ACCEPT(apr_proc_mutex_child_init(&process_accept_mutex, 
                                               ap_lock_fname, pchild));
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ap_server_conf,
