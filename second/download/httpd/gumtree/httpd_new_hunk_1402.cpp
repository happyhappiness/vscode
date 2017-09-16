        }

        else if (!strcmp(tag, "var")) {

            var = tag_val;

        }

        else if (!strcmp(tag, "value")) {

            if (var == (char *) NULL) {

                ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,

                            "variable must precede value in set directive in %s",

			    r->filename);

                ap_rputs(error, r);

                return -1;

            }

            parse_string(r, tag_val, parsed_string, sizeof(parsed_string), 0);

            ap_table_setn(r->subprocess_env, var, ap_pstrdup(r->pool, parsed_string));

        }

        else {

            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,

                        "Invalid tag for set directive in %s", r->filename);

            ap_rputs(error, r);

            return -1;

        }

    }

}

