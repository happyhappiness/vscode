                    interpreter = "";
                }
            }
        }
    }
    if (!interpreter) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02102)
                      "%s is not executable; ensure interpreted scripts have "
                      "\"#!\" or \"'!\" first line", *cmd);
        return APR_EBADF;
    }

    *argv = (const char **)(split_argv(p, interpreter, *cmd,
                                       args)->elts);
    *cmd = (*argv)[0];
