        return DECLINED;

    if (strcmp(r->handler, "ldap-status")) {
        return DECLINED;
    }

    ap_set_content_type(r, "text/html; charset=ISO-8859-1");

    if (r->header_only)
        return OK;

    ap_rputs(DOCTYPE_HTML_3_2
             "<html><head><title>LDAP Cache Information</title></head>\n", r);
    ap_rputs("<body bgcolor='#ffffff'><h1 align=center>LDAP Cache Information"
