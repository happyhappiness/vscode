static int ssl_ext_status_hook(request_rec *r, int flags)
{
    SSLSrvConfigRec *sc = mySrvConfig(r->server);

    if (sc == NULL || flags & AP_STATUS_SHORT)
        return OK;

    ap_rputs("<hr>\n", r);
    ap_rputs("<table cellspacing=0 cellpadding=0>\n", r);
    ap_rputs("<tr><td bgcolor=\"#000000\">\n", r);
    ap_rputs("<b><font color=\"#ffffff\" face=\"Arial,Helvetica\">SSL/TLS Session Cache Status:</font></b>\r", r);
    ap_rputs("</td></tr>\n", r);
    ap_rputs("<tr><td bgcolor=\"#ffffff\">\n", r);

    if (sc->mc->nSessionCacheMode == SSL_SCMODE_DBM)
        ssl_scache_dbm_status(r, flags, r->pool);
    else if (sc->mc->nSessionCacheMode == SSL_SCMODE_SHMCB)
        ssl_scache_shmcb_status(r, flags, r->pool);
#ifdef HAVE_DISTCACHE
    else if (sc->mc->nSessionCacheMode == SSL_SCMODE_DC)
        ssl_scache_dc_status(r, flags, r->pool);
#endif

    ap_rputs("</td></tr>\n", r);
    ap_rputs("</table>\n", r);
    return OK;
}