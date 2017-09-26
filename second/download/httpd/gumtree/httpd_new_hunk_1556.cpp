
module AP_MODULE_DECLARE_DATA dumpio_module ;

typedef struct dumpio_conf_t {
    int enable_input;
    int enable_output;
    int loglevel;
} dumpio_conf_t;

/*
 * Workhorse function: simply log to the current error_log
 * info about the data in the bucket as well as the data itself
 */
static void dumpit(ap_filter_t *f, apr_bucket *b)
{
    conn_rec *c = f->c;
    dumpio_conf_t *ptr =
    (dumpio_conf_t *) ap_get_module_config(c->base_server->module_config,
                                           &dumpio_module);

    ap_log_error(APLOG_MARK, ptr->loglevel, 0, c->base_server,
        "mod_dumpio:  %s (%s-%s): %" APR_SIZE_T_FMT " bytes",
                f->frec->name,
                (APR_BUCKET_IS_METADATA(b)) ? "metadata" : "data",
                b->type->name,
                b->length) ;

