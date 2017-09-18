                expansion = in - 1;
                if (*in == '{') {
                    ++in;
                    start_of_var_name = in;
                    in = ap_strchr_c(in, '}');
                    if (in == NULL) {
                        ap_log_rerror(APLOG_MARK, APLOG_ERR,
                                      0, r, "Missing '}' on variable \"%s\"",
                                      expansion);
                        *next = '\0';
                        return out;
                    }
                    temp_end = in;
