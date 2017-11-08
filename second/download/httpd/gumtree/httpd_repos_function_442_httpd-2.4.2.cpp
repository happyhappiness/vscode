static config_log_state *open_config_log(server_rec *s, apr_pool_t *p,
                                         config_log_state *cls,
                                         apr_array_header_t *default_format)
{
    if (cls->log_writer != NULL) {
        return cls;             /* virtual config shared w/main server */
    }

    if (cls->fname == NULL) {
        return cls;             /* Leave it NULL to decline.  */
    }

    cls->log_writer = log_writer_init(p, s, cls->fname);
    if (cls->log_writer == NULL)
        return NULL;

    return cls;
}