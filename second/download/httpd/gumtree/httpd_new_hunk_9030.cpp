	    hStdErr = dup(fileno(stderr));
	    if(dup2(err_fds[1], fileno(stderr)))
		ap_log_error(APLOG_MARK, APLOG_ERR, NULL, "dup2(stdin) failed");
	    close(err_fds[1]);
	}

	info.hPipeInputRead   = GetStdHandle(STD_INPUT_HANDLE);
	info.hPipeOutputWrite = GetStdHandle(STD_OUTPUT_HANDLE);
	info.hPipeErrorWrite  = GetStdHandle(STD_ERROR_HANDLE);

	pid = (*func) (data, &info);
        if (pid == -1) pid = 0;   /* map Win32 error code onto Unix default */

        if (!pid) {
	    save_errno = errno;
	    close(in_fds[1]);
	    close(out_fds[0]);
++ apache_1.3.2/src/main/buff.c	1998-09-05 00:47:46.000000000 +0800
