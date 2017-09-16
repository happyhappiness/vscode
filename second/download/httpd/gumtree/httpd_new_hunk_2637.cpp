            ap_chdir_file(r->filename);

#endif

        }

        else if (!strcmp(tag, "cgi")) {

            parse_string(r, tag_val, parsed_string, sizeof(parsed_string), 0);

            if (include_cgi(parsed_string, r) == -1) {

                ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,

                            "invalid CGI ref \"%s\" in %s", tag_val, file);

                ap_rputs(error, r);

            }

            /* grumble groan */

#ifndef WIN32

            ap_chdir_file(r->filename);

#endif

        }

        else if (!strcmp(tag, "done")) {

            return 0;

        }

        else {

            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,

                        "unknown parameter \"%s\" to tag exec in %s",

                        tag, file);

            ap_rputs(error, r);

        }

    }



