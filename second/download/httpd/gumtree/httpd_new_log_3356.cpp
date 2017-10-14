apr_file_printf(out, "User: name=\"%s\" id=%lu%s\n",
                    ap_unixd_config.user_name, (unsigned long)uid, no_root);