static int log_init(apr_pool_t *pc, apr_pool_t *p, apr_pool_t *pt,
                     server_rec *s)
{
    for ( ; s ; s = s->next) {
        if (!open_log(s, p)) {
            return HTTP_INTERNAL_SERVER_ERROR;
        }
    }

    return OK;
}