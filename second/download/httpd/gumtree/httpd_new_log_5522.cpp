apr_file_printf(out, "PidFile: \"%s\"\n",
                    ap_server_root_relative(p, ap_pid_fname));