static int core_create_req(request_rec *r)
{
    /* Alloc the config struct and the array of request notes in
     * a single block for efficiency
     */
    core_request_config *req_cfg;

    req_cfg = apr_pcalloc(r->pool, sizeof(core_request_config) +
                          sizeof(void *) * num_request_notes);
    req_cfg->notes = (void **)((char *)req_cfg + sizeof(core_request_config));

    /* ### temporarily enable script delivery as the default */
    req_cfg->deliver_script = 1;

    if (r->main) {
        core_request_config *main_req_cfg = (core_request_config *)
            ap_get_module_config(r->main->request_config, &core_module);
        req_cfg->bb = main_req_cfg->bb;
    }
    else {
        req_cfg->bb = apr_brigade_create(r->pool, r->connection->bucket_alloc);
        if (!r->prev) {
            ap_add_input_filter_handle(ap_net_time_filter_handle,
                                       NULL, r, r->connection);
        }
    }

    ap_set_module_config(r->request_config, &core_module, req_cfg);

    /* Begin by presuming any module can make its own path_info assumptions,
     * until some module interjects and changes the value.
     */
    r->used_path_info = AP_REQ_DEFAULT_PATH_INFO;

    return OK;
}