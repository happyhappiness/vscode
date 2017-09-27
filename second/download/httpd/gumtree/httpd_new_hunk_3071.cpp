                     * borked (there's plenty of room for a race condition).
                     * Either the backend sets it or it's gonna be chunked.
                     */
                    ap_run_sub_req(rr);
                }
                else {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00864)
                                  "Subrequest to file '%s' not possible. "
                                  "(rr->status=%d, rr->finfo.filetype=%d)",
                                  req_conf->location, rr->status,
                                  rr->finfo.filetype);
                    *status = HTTP_INTERNAL_SERVER_ERROR;
                    return *status;
