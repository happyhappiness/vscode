char *ap_response_code_string(request_rec *r, int error_index)
{
    core_dir_config *conf;

    conf = (core_dir_config *)ap_get_module_config(r->per_dir_config,
                                                   &core_module);

    if (conf->response_code_strings == NULL) {
        return NULL;
    }

    return conf->response_code_strings[error_index];
}