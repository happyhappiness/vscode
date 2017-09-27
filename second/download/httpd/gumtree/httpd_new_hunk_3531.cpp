                if (apr_isprint(*cp) && !apr_isprint(native))
                    ++maybeEBCDIC;
                if (!apr_isprint(*cp) && apr_isprint(native))
                    ++maybeASCII;
            }
            if (maybeASCII > maybeEBCDIC) {
                ap_log_error(SCRIPT_LOG_MARK, APLOG_ERR, 0, r->server,
                             "CGI Interface Error: Script headers apparently ASCII: (CGI = %s)",
                             r->filename);
                inbytes_left = outbytes_left = cp - w;
                apr_xlate_conv_buffer(ap_hdrs_from_ascii,
                                      w, &inbytes_left, w, &outbytes_left);
            }
        }
#endif /*APR_CHARSET_EBCDIC*/
        if (!(l = strchr(w, ':'))) {
            if (!buffer) {
                /* Soak up all the script output - may save an outright kill */
                while ((*getsfunc) (w, MAX_STRING_LEN - 1, getsfunc_data)) {
                    continue;
                }
            }

            ap_log_rerror(SCRIPT_LOG_MARK, APLOG_ERR|APLOG_TOCLIENT, 0, r,
                          "malformed header from script '%s': Bad header: %.30s",
                          apr_filepath_name_get(r->filename), w);
            return HTTP_INTERNAL_SERVER_ERROR;
        }

        *l++ = '\0';
        while (*l && apr_isspace(*l)) {
            ++l;
