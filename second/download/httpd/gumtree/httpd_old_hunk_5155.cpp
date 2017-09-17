	memset(&si, 0, sizeof(si));
	memset(&pi, 0, sizeof(pi));

	interpreter[0] = 0;
	pid = -1;

	exename = strrchr(r->filename, '/');
	if (!exename) {
	    exename = strrchr(r->filename, '\\');
	}
	if (!exename) {
	    exename = r->filename;
	}
	else {
	    exename++;
	}
	dot = strrchr(exename, '.');
	if (dot) {
	    if (!strcasecmp(dot, ".BAT")
		|| !strcasecmp(dot, ".CMD")
		|| !strcasecmp(dot, ".EXE")
		||  !strcasecmp(dot, ".COM")) {
		is_exe = 1;
	    }
	}

	if (!is_exe) {
	    program = fopen(r->filename, "rb");
	    if (!program) {
		ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
			     "fopen(%s) failed", r->filename);
		return (pid);
	    }
	    sz = fread(interpreter, 1, sizeof(interpreter) - 1, program);
	    if (sz < 0) {
		ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
			     "fread of %s failed", r->filename);
		fclose(program);
		return (pid);
	    }
	    interpreter[sz] = 0;
	    fclose(program);
	    if (!strncmp(interpreter, "#!", 2)) {
		is_script = 1;
		for (i = 2; i < sizeof(interpreter); i++) {
		    if ((interpreter[i] == '\r')
			|| (interpreter[i] == '\n')) {
			break;
		    }
		}
		interpreter[i] = 0;
		for (i = 2; interpreter[i] == ' '; ++i)
		    ;
		memmove(interpreter+2,interpreter+i,strlen(interpreter+i)+1);
	    }
	    else {
	        /* Check to see if it's a executable */
                IMAGE_DOS_HEADER *hdr = (IMAGE_DOS_HEADER*)interpreter;
                if (hdr->e_magic == IMAGE_DOS_SIGNATURE && hdr->e_cblp < 512) {
                    is_binary = 1;
		}
	    }
	}
        /* Bail out if we haven't figured out what kind of
         * file this is by now..
         */
        if (!is_exe && !is_script && !is_binary) {
            ap_log_error(APLOG_MARK, APLOG_ERR|APLOG_NOERRNO, r->server,
		"%s is not executable; ensure interpreted scripts have "
		"\"#!\" first line", 
		r->filename);
            return (pid);
	}

	/*
	 * Make child process use hPipeOutputWrite as standard out,
	 * and make sure it does not show on screen.
	 */
	si.cb = sizeof(si);
	si.dwFlags     = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	si.wShowWindow = SW_HIDE;
	si.hStdInput   = pinfo->hPipeInputRead;
	si.hStdOutput  = pinfo->hPipeOutputWrite;
	si.hStdError   = pinfo->hPipeErrorWrite;

	if ((!r->args) || (!r->args[0]) || strchr(r->args, '=')) { 
	    if (is_exe || is_binary) {
	        /*
	         * When the CGI is a straight binary executable, 
		 * we can run it as is
	         */
	        pCommand = r->filename;
	    }
	    else if (is_script) {
                /* When an interpreter is needed, we need to create 
                 * a command line that has the interpreter name
                 * followed by the CGI script name.  
		 */
	        pCommand = ap_pstrcat(r->pool, interpreter + 2, " ", 
				      r->filename, NULL);
	    }
	    else {
	        /* If not an executable or script, just execute it
                 * from a command prompt.  
                 */
	        pCommand = ap_pstrcat(r->pool, SHELL_PATH, " /C ", 
				      r->filename, NULL);
	    }
	}
	else {

            /* If we are in this leg, there are some other arguments
             * that we must include in the execution of the CGI.
