static void ap_request_insert_filter(request_rec * r)
{
    request_dir_conf *conf = ap_get_module_config(r->per_dir_config,
                                                  &request_module);

    if (r->kept_body) {
        if (!request_is_filter_present(r, kept_body_input_filter_handle)) {
            ap_add_input_filter_handle(kept_body_input_filter_handle,
                                       NULL, r, r->connection);
        }
    }
    else if (conf->keep_body) {
        if (!request_is_filter_present(r, kept_body_input_filter_handle)) {
            ap_add_input_filter_handle(keep_body_input_filter_handle,
                                       NULL, r, r->connection);
        }
    }

}