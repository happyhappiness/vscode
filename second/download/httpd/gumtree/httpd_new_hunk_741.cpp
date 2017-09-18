	    int maybeASCII = 0, maybeEBCDIC = 0;
	    unsigned char *cp, native;
            apr_size_t inbytes_left, outbytes_left;

	    for (cp = w; *cp != '\0'; ++cp) {
                native = apr_xlate_conv_byte(ap_hdrs_from_ascii, *cp);
		if (apr_isprint(*cp) && !apr_isprint(native))
		    ++maybeEBCDIC;
		if (!apr_isprint(*cp) && apr_isprint(native))
		    ++maybeASCII;
            }
	    if (maybeASCII > maybeEBCDIC) {
		ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                             "CGI Interface Error: Script headers apparently ASCII: (CGI = %s)",
                             r->filename);
