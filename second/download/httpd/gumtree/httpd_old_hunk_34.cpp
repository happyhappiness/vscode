                     == INTERPRETER_SOURCE_REGISTRY_STRICT)) {
         /* Check the registry */
        int strict = (d->script_interpreter_source 
                      == INTERPRETER_SOURCE_REGISTRY_STRICT);
        interpreter = get_interpreter_from_win32_registry(r->pool, ext,
                                                          strict);
        if (interpreter && *type != APR_SHELLCMD) {
            *type = APR_PROGRAM_PATH;
        }
        else {
            ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_INFO, 0, r->server,
                 strict ? "No ExecCGI verb found for files of type '%s'."
                        : "No ExecCGI or Open verb found for files of type '%s'.", 
                 ext);
        }
    }
    if (!interpreter) {
