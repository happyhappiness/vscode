apr_status_t h2_request_end_headers(h2_request *req, struct h2_mplx *m,
                                    h2_task *task, int eos)
{
    if (!req->to_h1) {
        apr_status_t status = insert_request_line(req, m);
        if (status != APR_SUCCESS) {
            return status;
        }
    }
    return h2_to_h1_end_headers(req->to_h1, task, eos);
}