
        apr_rfc822_date(datestr, mod_time);
        apr_table_setn(r->headers_out, "Last-Modified", datestr);
    }
}

AP_IMPLEMENT_HOOK_RUN_ALL(int,post_read_request,
                          (request_rec *r), (r), OK, DECLINED)
AP_IMPLEMENT_HOOK_RUN_ALL(int,log_transaction,
                          (request_rec *r), (r), OK, DECLINED)
AP_IMPLEMENT_HOOK_RUN_FIRST(const char *,http_scheme,
                            (const request_rec *r), (r), NULL)
