AP_DECLARE(void) ap_send_interim_response(request_rec *r, int send_headers)
{
    hdr_ptr x;
    char *status_line = NULL;
    request_rec *rr;

    if (r->proto_num < HTTP_VERSION(1,1)) {
        /* don't send interim response to HTTP/1.0 Client */
        return;
    }
    if (!ap_is_HTTP_INFO(r->status)) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00575)
                      "Status is %d - not sending interim response", r->status);
