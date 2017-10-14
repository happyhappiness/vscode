apr_file_printf(out, "Group: name=\"%s\" id=%lu%s\n",
                    ap_unixd_config.group_name, (unsigned long)gid, no_root);