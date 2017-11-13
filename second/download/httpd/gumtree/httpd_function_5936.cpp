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
    ext = strrchr(apr_filepath_name_get(*cmd), '.');

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
        apr_size_t i;

        /* Need to peek into the file figure out what it really is...
         * ### aught to go back and build a cache for this one of these days.
         */
        if ((rv = apr_file_open(&fh, *cmd, APR_READ | APR_BUFFERED,
                                 APR_OS_DEFAULT, r->pool)) != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(02100)
                          "Failed to open cgi file %s for testing", *cmd);
            return rv;
        }
        if ((rv = apr_file_read(fh, buffer, &bytes)) != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(02101)
                          "Failed to read cgi file %s for testing", *cmd);
            return rv;
        }
        apr_file_close(fh);

        /* Some twisted character [no pun intended] at MS decided that a
         * zero width joiner as the lead wide character would be ideal for
         * describing Unicode text files.  This was further convoluted to
         * another MSism that the same character mapped into utf-8, EF BB BF
         * would signify utf-8 text files.
         *
         * Since MS configuration files are all protecting utf-8 encoded
         * Unicode path, file and resource names, we already have the correct
         * WinNT encoding.  But at least eat the stupid three bytes up front.
         *
         * ### A more thorough check would also allow UNICODE text in buf, and
         * convert it to UTF-8 for invoking unicode scripts.  Those are few
         * and far between, so leave that code an enterprising soul with a need.
         */
        if ((bytes >= 3) && memcmp(buffer, "\xEF\xBB\xBF", 3) == 0) {
            memmove(buffer, buffer + 3, bytes -= 3);
        }

        /* Script or executable, that is the question...
         * we check here also for '! so that .vbs scripts can work as CGI.
         */
        if ((bytes >= 2) && ((buffer[0] == '#') || (buffer[0] == '\''))
                         && (buffer[1] == '!')) {
            /* Assuming file is a script since it starts with a shebang */
            for (i = 2; i < bytes; i++) {
                if ((buffer[i] == '\r') || (buffer[i] == '\n')) {
                    buffer[i] = '\0';
                    break;
                }
            }
            if (i < bytes) {
                interpreter = buffer + 2;
                while (apr_isspace(*interpreter)) {
                    ++interpreter;
                }
                if (e_info->cmd_type != APR_SHELLCMD) {
                    e_info->cmd_type = APR_PROGRAM_PATH;
                }
            }
        }
        else if (bytes >= sizeof(IMAGE_DOS_HEADER)) {
            /* Not a script, is it an executable? */
            IMAGE_DOS_HEADER *hdr = (IMAGE_DOS_HEADER*)buffer;
            if (hdr->e_magic == IMAGE_DOS_SIGNATURE) {
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
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02102)
                      "%s is not executable; ensure interpreted scripts have "
                      "\"#!\" or \"'!\" first line", *cmd);
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
        if (elts[i].key && *elts[i].key && *elts[i].val
                && !(strncmp(elts[i].key, "REMOTE_", 7) == 0
                || strcmp(elts[i].key, "GATEWAY_INTERFACE") == 0
                || strcmp(elts[i].key, "REQUEST_METHOD") == 0
                || strcmp(elts[i].key, "SERVER_ADDR") == 0
                || strcmp(elts[i].key, "SERVER_PORT") == 0
                || strcmp(elts[i].key, "SERVER_PROTOCOL") == 0)) {
            prep_string((const char**) &elts[i].val, r->pool);
        }
    }
    return APR_SUCCESS;
}