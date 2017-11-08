static magic_req_rec *magic_set_config(request_rec *r)
{
    magic_req_rec *req_dat = (magic_req_rec *) apr_palloc(r->pool,
                                                      sizeof(magic_req_rec));

    req_dat->head = req_dat->tail = (magic_rsl *) NULL;
    ap_set_module_config(r->request_config, &mime_magic_module, req_dat);
    return req_dat;
}