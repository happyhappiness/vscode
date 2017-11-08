char *ap_response_code_string(request_rec *r, int error_index)
{
    core_dir_config *dirconf;
    core_request_config *reqconf;

    /* check for string registered via ap_custom_response() first */
    reqconf = (core_request_config *)ap_get_module_config(r->request_config,
                                                          &core_module);
    if (reqconf->response_code_strings != NULL &&
        reqconf->response_code_strings[error_index] != NULL) {
        return reqconf->response_code_strings[error_index];
    }

    /* check for string specified via ErrorDocument */
    dirconf = (core_dir_config *)ap_get_module_config(r->per_dir_config,
                                                      &core_module);

    if (dirconf->response_code_strings == NULL) {
	return NULL;
    }

    if (dirconf->response_code_strings[error_index] == &errordocument_default) {
        return NULL;
    }

    return dirconf->response_code_strings[error_index];
}