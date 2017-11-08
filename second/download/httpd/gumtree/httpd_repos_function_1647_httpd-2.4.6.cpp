static ap_configfile_t *make_array_config(apr_pool_t * pool,
                                          apr_array_header_t * contents,
                                          const char *where,
                                          ap_configfile_t * cfg,
                                          ap_configfile_t ** upper)
{
    array_contents_t *ls =
        (array_contents_t *) apr_palloc(pool, sizeof(array_contents_t));
    ap_assert(ls!=NULL);

    ls->index = 0;
    ls->char_index = 0;
    ls->contents = contents;
    ls->length = ls->contents->nelts < 1 ?
        0 : strlen(((char **) ls->contents->elts)[0]);
    ls->next = cfg;
    ls->upper = upper;

    return ap_pcfg_open_custom(pool, where, (void *) ls,
                               array_getch, array_getstr, array_close);
}