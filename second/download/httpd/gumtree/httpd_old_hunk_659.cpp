            return log_scripterror(r, conf, HTTP_FORBIDDEN, 0,
                                   "file permissions deny server execution");
    }

*/
    ap_add_common_vars(r);

    e_info.process_cgi = 1;
    e_info.cmd_type    = APR_PROGRAM;
    e_info.detached    = 0;
    e_info.in_pipe     = APR_CHILD_BLOCK;
    e_info.out_pipe    = APR_CHILD_BLOCK;
