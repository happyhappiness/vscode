static void ap_register_log_handler(apr_pool_t *p, char *tag,
                                    ap_log_handler_fn_t *handler, int def)
{
    ap_log_handler *log_struct = apr_palloc(p, sizeof(*log_struct));
    log_struct->func = handler;
    log_struct->want_orig_default = def;

    apr_hash_set(log_hash, tag, 1, (const void *)log_struct);
}