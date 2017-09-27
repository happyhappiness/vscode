    int error_index = ap_index_of_response(type);
    char *custom_response = ap_response_code_string(r, error_index);
    int recursive_error = 0;
    request_rec *r_1st_err = r;

    if (type == AP_FILTER_ERROR) {
        return;
    }

    if (type == DONE) {
        ap_finalize_request_protocol(r);
        return;
    }
