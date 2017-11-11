static apr_status_t ap_cgi_build_command(const char **cmd, const char ***argv,
                                         request_rec *r, apr_pool_t *p, 
                                         cgi_exec_info_t *e_info)
{
    const apr_array_header_t *elts_arr = apr_table_elts(r->subprocess_env);
    const apr_table_entry_t *elts = (apr_table_entry_t *) elts_arr->elts;
    const char *ext = NULL;
    const char *interpreter = NULL;
    win32_dir_conf *d;
    apr_file_t *fh;
    const char *args = "";
    int i;

    d = (win32_dir_conf *)ap_get_module_config(r->per_dir_config, 
                                               &win32_module);

    if (e_info->cmd_type) {
        /* We have to consider that the client gets any QUERY_ARGS
         * without any charset interpretation, use prep_string to
         * create a string of the literal QUERY_ARGS bytes.
         */
        *cmd = r->filename;
        if (r->args && r->args[0] && !ap_strchr_c(r->args, '=')) {
            args = r->args;
        }
    }
    /* Handle the complete file name, we DON'T want to follow suexec, since
     * an unrooted command is as predictable as shooting craps in Win32.
     * Notice that unlike most mime extension parsing, we have to use the
     * win32 parsing here, therefore the final extension is the only one
     * we will consider.
     */
    ext = strrchr(apr_filename_of_pathname(*cmd), '.');
    
    /* If the file has an extension and it is not .com and not .exe and
     * we've been instructed to search the registry, then do so.
     * Let apr_proc_create do all of the .bat/.cmd dirty work.
     */
    if (ext && (!strcasecmp(ext,".exe") || !strcasecmp(ext,".com")
                || !strcasecmp(ext,".bat") || !strcasecmp(ext,".cmd"))) {
        interpreter = "";
    }
    if (!interpreter && ext 
          && (d->script_interpreter_source 
                     == INTERPRETER_SOURCE_REGISTRY
           || d->script_interpreter_source 
                     == INTERPRETER_SOURCE_REGISTRY_STRICT)) {
         /* Check the registry */
        int strict = (d->script_interpreter_source 
                      == INTERPRETER_SOURCE_REGISTRY_STRICT);
        interpreter = get_interpreter_from_win32_registry(r->pool, ext,
                                                          strict);
        if (interpreter && e_info->cmd_type != APR_SHELLCMD) {
            e_info->cmd_type = APR_PROGRAM_PATH;
        }
        else {
            ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                 strict ? "No ExecCGI verb found for files of type '%s'."
                        : "No ExecCGI or Open verb found for files of type '%s'.", 
                 ext);
        }
    }
    if (!interpreter) {
        apr_status_t rv;
        char buffer[1024];
        apr_size_t bytes = sizeof(buffer);
        int i;

        /* Need to peek into the file figure out what it really is... 
         * ### aught to go back and build a cache for this one of these days.
         */
        if (((rv = apr_file_open(&fh, *cmd, APR_READ | APR_BUFFERED,
                                 APR_OS_DEFAULT, r->pool)) != APR_SUCCESS) 
            || ((rv = apr_file_read(fh, buffer, &bytes)) != APR_SUCCESS)) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "Failed to read cgi file %s for testing", *cmd);
            return rv;
        }
        apr_file_close(fh);

        /* Script or executable, that is the question... */
        if ((buffer[0] == '#') && (buffer[1] == '!')) {
            /* Assuming file is a script since it starts with a shebang */
            for (i = 2; i < sizeof(buffer); i++) {
                if ((buffer[i] == '\r') || (buffer[i] == '\n')) {
                    buffer[i] = '\0';
                    break;
                }
            }
            if (i < sizeof(buffer)) {
                interpreter = buffer + 2;
                while (apr_isspace(*interpreter)) {
                    ++interpreter;
                }
                if (e_info->cmd_type != APR_SHELLCMD) {
                    e_info->cmd_type = APR_PROGRAM_PATH;
                }
            }
        }
        else {
            /* Not a script, is it an executable? */
            IMAGE_DOS_HEADER *hdr = (IMAGE_DOS_HEADER*)buffer;    
            if ((bytes >= sizeof(IMAGE_DOS_HEADER))
                && (hdr->e_magic == IMAGE_DOS_SIGNATURE)) {
                if (hdr->e_lfarlc < 0x40) {
                    /* Ought to invoke this 16 bit exe by a stub, (cmd /c?) */
                    interpreter = "";
                }
                else {
                    interpreter = "";
                }
            }
        }
    }
    if (!interpreter) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "%s is not executable; ensure interpreted scripts have "
                      "\"#!\" first line", *cmd);
        return APR_EBADF;
    }

    *argv = (const char **)(split_argv(p, interpreter, *cmd,
                                       args)->elts);
    *cmd = (*argv)[0];

    e_info->detached = 1;

    /* XXX: Must fix r->subprocess_env to follow utf-8 conventions from
     * the client's octets so that win32 apr_proc_create is happy.
     * The -best- way is to determine if the .exe is unicode aware
     * (using 0x0080-0x00ff) or is linked as a command or windows
     * application (following the OEM or Ansi code page in effect.)
     */
    for (i = 0; i < elts_arr->nelts; ++i) {
        if (win_nt && elts[i].key && *elts[i].key 
                && (strncmp(elts[i].key, "HTTP_", 5) == 0
                 || strncmp(elts[i].key, "SERVER_", 7) == 0
                 || strncmp(elts[i].key, "REQUEST_", 8) == 0
                 || strcmp(elts[i].key, "QUERY_STRING") == 0
                 || strcmp(elts[i].key, "PATH_INFO") == 0
                 || strcmp(elts[i].key, "PATH_TRANSLATED") == 0)) {
            prep_string((const char**) &elts[i].val, r->pool);
        }
    }
    return APR_SUCCESS;
}