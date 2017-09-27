 */

char *ap_response_code_string(request_rec *r, int error_index)
{
    core_dir_config *dirconf;
    core_request_config *reqconf = ap_get_core_module_config(r->request_config);

    /* check for string registered via ap_custom_response() first */
    if (reqconf->response_code_strings != NULL &&
        reqconf->response_code_strings[error_index] != NULL) {
        return reqconf->response_code_strings[error_index];
    }

    /* check for string specified via ErrorDocument */
    dirconf = ap_get_core_module_config(r->per_dir_config);

    if (dirconf->response_code_strings == NULL) {
        return NULL;
    }

    if (dirconf->response_code_strings[error_index] == &errordocument_default) {
        return NULL;
    }

    return dirconf->response_code_strings[error_index];
}


/* Code from Harald Hanche-Olsen <hanche@imf.unit.no> */
static APR_INLINE void do_double_reverse (conn_rec *conn)
{
