    const fnames *f1 = fn1;
    const fnames *f2 = fn2;

    return strcmp(f1->fname,f2->fname);
}

AP_DECLARE(const char *) ap_process_resource_config(server_rec *s,
                                                    const char *fname,
                                                    ap_directive_t **conftree,
                                                    apr_pool_t *p,
                                                    apr_pool_t *ptemp)
{
