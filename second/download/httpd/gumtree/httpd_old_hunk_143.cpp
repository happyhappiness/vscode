	if (!ap_can_exec(&r->finfo))
	    return log_scripterror(r, conf, HTTP_FORBIDDEN, 0,
				   "file permissions deny server execution");
    }

*/
    if ((retval = ap_setup_client_block(r, REQUEST_CHUNKED_ERROR)))
	return retval;

    ap_add_common_vars(r);

    e_info.cmd_type  = APR_PROGRAM;
    e_info.in_pipe   = APR_CHILD_BLOCK;
    e_info.out_pipe  = APR_CHILD_BLOCK;
    e_info.err_pipe  = APR_CHILD_BLOCK;
    e_info.prog_type = RUN_AS_CGI;
    e_info.bb        = NULL;
    e_info.ctx       = NULL;
    e_info.next      = NULL;

    /* build the command line */
    if ((rv = cgi_build_command(&command, &argv, r, p, 1, &e_info.cmd_type)) 
            != APR_SUCCESS) {
	ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
		      "don't know how to spawn child process: %s", 
                      r->filename);
	return HTTP_INTERNAL_SERVER_ERROR;
    }

