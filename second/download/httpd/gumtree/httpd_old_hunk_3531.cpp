                if (apr_isprint(*cp) && !apr_isprint(native))
                    ++maybeEBCDIC;
                if (!apr_isprint(*cp) && apr_isprint(native))
                    ++maybeASCII;
            }
            if (maybeASCII > maybeEBCDIC) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                             "CGI Interface Error: Script headers apparently ASCII: (CGI = %s)",
                             r->filename);
                inbytes_left = outbytes_left = cp - w;
                apr_xlate_conv_buffer(ap_hdrs_from_ascii,
                                      w, &inbytes_left, w, &outbytes_left);
            }
        }
#endif /*APR_CHARSET_EBCDIC*/
        if (!(l = strchr(w, ':'))) {
            char malformed[(sizeof MALFORMED_MESSAGE) + 1
                           + MALFORMED_HEADER_LENGTH_TO_SHOW];

            strcpy(malformed, MALFORMED_MESSAGE);
            strncat(malformed, w, MALFORMED_HEADER_LENGTH_TO_SHOW);

            if (!buffer) {
                /* Soak up all the script output - may save an outright kill */
                while ((*getsfunc) (w, MAX_STRING_LEN - 1, getsfunc_data)) {
                    continue;
                }
            }

            ap_log_rerror(APLOG_MARK, APLOG_ERR|APLOG_TOCLIENT, 0, r,
                          "%s: %s", malformed,
                          apr_filepath_name_get(r->filename));
            return HTTP_INTERNAL_SERVER_ERROR;
        }

        *l++ = '\0';
        while (*l && apr_isspace(*l)) {
            ++l;
