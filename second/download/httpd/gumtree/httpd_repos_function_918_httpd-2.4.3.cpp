static int ssl_expr_lookup(ap_expr_lookup_parms *parms)
{
    switch (parms->type) {
    case AP_EXPR_FUNC_VAR:
        /* for now, we just handle everything that starts with SSL_, but
         * register our hook as APR_HOOK_LAST
         * XXX: This can be optimized
         */
        if (strcEQn(parms->name, "SSL_", 4)) {
            *parms->func = expr_var_fn;
            *parms->data = parms->name + 4;
            return OK;
        }
        break;
    case AP_EXPR_FUNC_LIST:
        if (strcEQ(parms->name, "PeerExtList")) {
            *parms->func = expr_peer_ext_list_fn;
            *parms->data = "PeerExtList";
            return OK;
        }
        break;
    }
    return DECLINED;
}