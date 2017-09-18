		if (isprint(*cp) && !isprint(native))
		    ++maybeEBCDIC;
		if (!isprint(*cp) && isprint(native))
		    ++maybeASCII;
            }
	    if (maybeASCII > maybeEBCDIC) {
		ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r->server,
                             "CGI Interface Error: Script headers apparently ASCII: (CGI = %s)",
                             r->filename);
                inbytes_left = outbytes_left = cp - w;
                apr_xlate_conv_buffer(ap_hdrs_from_ascii,
                                      w, &inbytes_left, w, &outbytes_left);
	    }
