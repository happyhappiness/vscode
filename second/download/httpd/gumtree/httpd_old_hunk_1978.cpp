    ap_rputs(" </HEAD>\n", r);
    ap_rputs(" <BODY>\n", r);
    ap_rputs("  <H1><SAMP>mod_example</SAMP> Module Content-Handler Output\n", r);
    ap_rputs("  </H1>\n", r);
    ap_rputs("  <P>\n", r);
    ap_rprintf(r, "  Apache HTTP Server version: \"%s\"\n",
            ap_get_server_version());
    ap_rputs("  <BR>\n", r);
    ap_rprintf(r, "  Server built: \"%s\"\n", ap_get_server_built());
    ap_rputs("  </P>\n", r);;
    ap_rputs("  <P>\n", r);
    ap_rputs("  The format for the callback trace is:\n", r);
    ap_rputs("  </P>\n", r);
