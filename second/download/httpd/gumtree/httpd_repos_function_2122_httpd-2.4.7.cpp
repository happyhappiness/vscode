static void *merge_scgi_config(apr_pool_t *p, void *base_, void *add_)
{
    scgi_config *base=base_, *add=add_, *conf=apr_palloc(p, sizeof(*conf));

    conf->sendfile = add->sendfile ? add->sendfile: base->sendfile;
    conf->internal_redirect =   (add->internal_redirect != -1)
                              ? add->internal_redirect
                              : base->internal_redirect;
    return conf;
}