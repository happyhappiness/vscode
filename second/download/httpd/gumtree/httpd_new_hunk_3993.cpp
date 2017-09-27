        return log_scripterror(r, conf, HTTP_NOT_FOUND, 0, APLOGNO(02813),
                               "AcceptPathInfo off disallows user's path");
    }
/*
    if (!ap_suexec_enabled) {
        if (!ap_can_exec(&r->finfo))
            return log_scripterror(r, conf, HTTP_FORBIDDEN, 0, APLOGNO(03194)
                                   "file permissions deny server execution");
    }

*/
    ap_add_common_vars(r);
    ap_add_cgi_vars(r);
