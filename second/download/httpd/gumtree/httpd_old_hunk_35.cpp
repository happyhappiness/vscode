                    interpreter = "";
                }
            }
        }
    }
    if (!interpreter) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR|APLOG_NOERRNO, 0, r,
                      "%s is not executable; ensure interpreted scripts have "
                      "\"#!\" first line", *cmd);
        return APR_EBADF;
    }

    *argv = (const char **)(split_argv(p, interpreter, *cmd,
                                       args)->elts);
    *cmd = (*argv)[0];
    return APR_SUCCESS;
}

APR_DECLARE_OPTIONAL_FN(apr_status_t, ap_cgi_build_command,
                        (const char **cmd, const char ***argv, 
                         request_rec *r, apr_pool_t *p, 
                         int replace_cmd, apr_cmdtype_e *type));

static void register_hooks(apr_pool_t *p)
{
    APR_REGISTER_OPTIONAL_FN(ap_cgi_build_command);
}

static const command_rec win32_cmds[] = {
