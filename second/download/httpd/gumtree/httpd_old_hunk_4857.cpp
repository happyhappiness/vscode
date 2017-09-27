    ap_rputs("  </H1>\n", r);
    ap_rputs("  <P>\n", r);
    ap_rprintf(r, "  Apache HTTP Server version: \"%s\"\n",
            ap_get_server_banner());
    ap_rputs("  <BR>\n", r);
    ap_rprintf(r, "  Server built: \"%s\"\n", ap_get_server_built());
    ap_rputs("  </P>\n", r);;
    ap_rputs("  <P>\n", r);
    ap_rputs("  The format for the callback trace is:\n", r);
    ap_rputs("  </P>\n", r);
    ap_rputs("  <DL>\n", r);
    ap_rputs("   <DT><EM>n</EM>.<SAMP>&lt;routine-name&gt;", r);
    ap_rputs("(&lt;routine-data&gt;)</SAMP>\n", r);
