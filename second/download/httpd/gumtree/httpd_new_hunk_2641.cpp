    ap_rputs("  namespace.\n", r);
    ap_rputs("  </P>\n", r);
    ap_rprintf(r, "  <H2>Startup callbacks so far:</H2>\n  <OL>\n%s  </OL>\n",
            trace);
    ap_rputs("  <H2>Connection-specific callbacks so far:</H2>\n", r);

    status =  apr_pool_userdata_get(&conn_data, CONN_NOTE,
                                    r->connection->pool);
    if ((status == APR_SUCCESS) && conn_data) {
        ap_rprintf(r, "  <OL>\n%s  </OL>\n", (char *) conn_data);
    } else {
        ap_rputs("  <P>No connection-specific callback information was "
                 "retrieved.</P>\n", r);
