static int authenticate_form_redirect_handler(request_rec * r)
{

    request_rec *rr = NULL;
    const char *sent_method = NULL, *sent_mimetype = NULL;

    if (strcmp(r->handler, FORM_REDIRECT_HANDLER)) {
        return DECLINED;
    }

    /* get the method and mimetype from the notes */
    get_notes_auth(r, NULL, NULL, &sent_method, &sent_mimetype);

    if (r->kept_body && sent_method && sent_mimetype) {

        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, LOG_PREFIX
          "internal redirect to method '%s' and body mimetype '%s' for the "
                      "uri: %s", sent_method, sent_mimetype, r->uri);

        rr = ap_sub_req_method_uri(sent_method, r->uri, r, r->output_filters);
        r->status = ap_run_sub_req(rr);

    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, LOG_PREFIX
        "internal redirect requested but one or all of method, mimetype or "
                      "body are NULL: %s", r->uri);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    /* return the underlying error, or OK on success */
    return r->status == HTTP_OK || r->status == OK ? OK : r->status;

}