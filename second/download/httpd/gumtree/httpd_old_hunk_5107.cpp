	    hStdErr = dup(fileno(stderr));
	    if(dup2(err_fds[1], fileno(stderr)))
		ap_log_error(APLOG_MARK, APLOG_ERR, NULL, "dup2(stdin) failed");
	    close(err_fds[1]);
	}

	pid = (*func) (data, NULL);
        if (pid == -1) pid = 0;   /* map Win32 error code onto Unix default */

        if (!pid) {
	    save_errno = errno;
	    close(in_fds[1]);
	    close(out_fds[0]);
-- apache_1.3.1/src/main/buff.c	1998-07-05 02:22:11.000000000 +0800
