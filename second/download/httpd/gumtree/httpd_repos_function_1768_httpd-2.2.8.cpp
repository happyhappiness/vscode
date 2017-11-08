static int x_handler(request_rec *r)
{
    x_cfg *dcfg;

    if (strcmp(r->handler, "example-handler")) {
        return DECLINED;
    }

    dcfg = our_dconfig(r);
    trace_add(r->server, r, dcfg, "x_handler()");
    /*
     * We're about to start sending content, so we need to force the HTTP
     * headers to be sent at this point.  Otherwise, no headers will be sent
     * at all.  We can set any we like first, of course.  **NOTE** Here's
     * where you set the "Content-type" header, and you do so by putting it in
     * r->content_type, *not* r->headers_out("Content-type").  If you don't
     * set it, it will be filled in with the server's default type (typically
     * "text/plain").  You *must* also ensure that r->content_type is lower
     * case.
     *
     * We also need to start a timer so the server can know if the connexion
     * is broken.
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
    ap_rputs("  <TITLE>mod_example Module Content-Handler Output\n", r);
    ap_rputs("  </TITLE>\n", r);
    ap_rputs(" </HEAD>\n", r);
    ap_rputs(" <BODY>\n", r);
    ap_rputs("  <H1><SAMP>mod_example</SAMP> Module Content-Handler Output\n", r);
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
    ap_rprintf(r, "  <H2>Static callbacks so far:</H2>\n  <OL>\n%s  </OL>\n",
            trace);
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
     * We did what we wanted to do, so tell the rest of the ser