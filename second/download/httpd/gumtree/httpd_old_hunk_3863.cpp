    }
    ap_fputs(x.f, x.bb, CRLF_ASCII);
    ap_fflush(x.f, x.bb);
    apr_brigade_destroy(x.bb);
}


AP_IMPLEMENT_HOOK_VOID(pre_read_request,
                       (request_rec *r, conn_rec *c),
                       (r, c))
AP_IMPLEMENT_HOOK_RUN_ALL(int,post_read_request,
                          (request_rec *r), (r), OK, DECLINED)
