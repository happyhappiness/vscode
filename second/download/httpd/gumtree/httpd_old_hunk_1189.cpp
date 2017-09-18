        return OK;

    ap_rputs(DOCTYPE_HTML_3_2
             "<html><head><title>LDAP Cache Information</title></head>\n", r);
    ap_rputs("<body bgcolor='#ffffff'><h1 align=center>LDAP Cache Information</h1>\n", r);

    ap_rputs("<p>\n"
             "<table border='0'>\n"
             "<tr bgcolor='#000000'>\n"
             "<td><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>Cache Name</b></font></td>"
             "<td><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>Entries</b></font></td>"
             "<td><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>Avg. Chain Len.</b></font></td>"
             "<td colspan='2'><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>Hits</b></font></td>"
             "<td><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>Ins/Rem</b></font></td>"
             "<td colspan='2'><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>Purges</b></font></td>"
             "<td><font size='-1' face='Arial,Helvetica' color='#ffffff'><b>Avg Purge Time</b></font></td>"
             "</tr>\n", r
            );

    ap_rputs(util_ald_cache_display(r->pool, st), r);

    ap_rputs("</table>\n</p>\n", r);

    return OK;
}

/* ------------------------------------------------------------------ */

