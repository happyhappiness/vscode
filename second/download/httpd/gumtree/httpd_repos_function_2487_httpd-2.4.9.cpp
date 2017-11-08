static int x_handler(request_rec *r)
{
    x_cfg *dcfg;
    char *note;
    void *conn_data;
    apr_status_t status;

    dcfg = our_dconfig(r);
    /*
     * Add our trace to the log, and whether we get to write
     * content for this request.
     */
    note = apr_pstrcat(r->pool, "x_handler(), handler is \"",
                      r->handler, "\"", NULL);
    trace_request(r, note);

    /* If it's not for us, get out as soon as possible. */
    if (strcmp(r->handler, "example-hooks-handler")) {
        return DECLINED;
    }

    /*
     * Set the Content-type header. Note that we do not actually have to send
     * the headers: this is done by the http core.
     */
    ap_set_content_type(r, "text/html");
    /*
     * If we're only supposed to send header information (HEAD request), we're
     * already there.
     */
    if (r->header_only) {
        return OK;
    }

    /*
     * Now send our actual output.  Since we tagged this as being
     * "text/html", we need to embed any HTML.
     */
    ap_rputs(DOCTYPE_HTML_3_2, r);
    ap_rputs("<HTML>\n", r);
    ap_rputs(" <HEAD>\n", r);
    ap_rputs("  <TITLE>mod_example_hooks Module Content-Handler Output\n", r);
    ap_rputs("  </TITLE>\n", r);
    ap_rputs(" </HEAD>\n", r);
    ap_rputs(" <BODY>\n", r);
    ap_rputs("  <H1><SAMP>mod_example_hooks</SAMP> Module Content-Handler Output\n", r);
    ap_rputs("  </H1>\n", r);
    ap_rputs("  <P>\n", r);
    ap_rprintf(r, "  Apache HTTP Server version: \"%s\"\n",
            ap_get_server_banner());
    ap_rputs("  <BR>\n", r);
    ap_rprintf(r, "  Server built: \"%s\"\n", ap_get_server_built());
    ap_rputs("  </P>\n", r);
    ap_rputs("  <P>\n", r);
    ap_rputs("  The format for the callback trace is:\n", r);
    ap_rputs("  </P>\n", r);
    ap_rputs("  <DL>\n", r);
    ap_rputs("   <DT><EM>n</EM>.<SAMP>&lt;routine-name&gt;", r);
    ap_rputs("(&lt;routine-data&gt;)</SAMP>\n", r);
    ap_rputs("   </DT>\n", r);
    ap_rputs("   <DD><SAMP>[&lt;applies-to&gt;]</SAMP>\n", r);
    ap_rputs("   </DD>\n", r);
    ap_rputs("  </DL>\n", r);
    ap_rputs("  <P>\n", r);
    ap_rputs("  The <SAMP>&lt;routine-data&gt;</SAMP> is supplied by\n", r);
    ap_rputs("  the routine when it requests the trace,\n", r);
    ap_rputs("  and the <SAMP>&lt;applies-to&gt;</SAMP> is extracted\n", r);
    ap_rputs("  from the configuration record at the time of the trace.\n", r);
    ap_rputs("  <STRONG>SVR()</STRONG> indicates a server environment\n", r);
    ap_rputs("  (blank means the main or default server, otherwise it's\n", r);
    ap_rputs("  the name of the VirtualHost); <STRONG>DIR()</STRONG>\n", r);
    ap_rputs("  indicates a location in the URL or filesystem\n", r);
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
    }

    ap_rputs("  <H2>Request-specific callbacks so far:</H2>\n", r);
    ap_rprintf(r, "  <OL>\n%s  </OL>\n", apr_table_get(r->notes, TRACE_NOTE));
    ap_rputs("  <H2>Environment for <EM>this</EM> call:</H2>\n", r);
    ap_rputs("  <UL>\n", r);
    ap_rprintf(r, "   <LI>Applies-to: <SAMP>%s</SAMP>\n   </LI>\n", dcfg->loc);
    ap_rprintf(r, "   <LI>\"Example\" directive declared here: %s\n   </LI>\n",
            (dcfg->local ? "YES" : "NO"));
    ap_rprintf(r, "   <LI>\"Example\" inherited: %s\n   </LI>\n",
            (dcfg->congenital ? "YES" : "NO"));
    ap_rputs("  </UL>\n", r);
    ap_rputs(" </BODY>\n", r);
    ap_rputs("</HTML>\n", r);
    /*
     * We're all done, so cancel the timeout we set.  Since this is probably
     * the end of the request we *could* assume this would be done during
     * post-processing - but it's possible that another handler might be
     * called and inherit our outstanding timer.  Not good; to each its own.
     */
    /*
     * We did what we wanted to do, so tell the rest of the server we
     * succeeded.
     */
    return OK;
}