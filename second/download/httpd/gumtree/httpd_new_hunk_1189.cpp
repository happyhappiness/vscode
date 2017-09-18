        return OK;

    ap_rputs(DOCTYPE_HTML_3_2
             "<html><head><title>LDAP Cache Information</title></head>\n", r);
    ap_rputs("<body bgcolor='#ffffff'><h1 align=center>LDAP Cache Information</h1>\n", r);

    util_ald_cache_display(r, st);

    return OK;
}

/* ------------------------------------------------------------------ */

