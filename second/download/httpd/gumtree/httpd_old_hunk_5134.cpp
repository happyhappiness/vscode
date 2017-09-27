        }
    }

    /*
     * Now break apart the line and compare each word on it
     */
    t = require_args;
    while ((w = ap_getword_conf(r->pool, &t)) && w[0]) {
        result = util_ldap_cache_compare(r, ldc, sec->url, req->dn, sec->attribute, w);
        switch(result) {
            case LDAP_COMPARE_TRUE: {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01705)
                              "auth_ldap authorize: "
