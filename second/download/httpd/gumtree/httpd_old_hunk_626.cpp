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
