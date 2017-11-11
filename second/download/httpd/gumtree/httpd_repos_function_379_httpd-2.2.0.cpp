static const char *log_remote_host(request_rec *r, char *a)
{
    return ap_escape_logitem(r->pool, ap_get_remote_host(r->connection,
                                                         r->per_dir_config,
                                                         REMOTE_NAME, NULL));
}