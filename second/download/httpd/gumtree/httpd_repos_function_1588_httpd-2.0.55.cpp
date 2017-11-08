static apr_status_t x_child_exit(void *data)
{
    char *note;
    server_rec *s = data;
    char *sname = s->server_hostname;

    /*
     * The arbitrary text we add to our trace entry indicates for which server
     * we're being called.
     */
    sname = (sname != NULL) ? sname : "";
    note = apr_pstrcat(s->process->pool, "x_child_exit(", sname, ")", NULL);
    trace_add(s, NULL, NULL, note);
    return APR_SUCCESS;
}