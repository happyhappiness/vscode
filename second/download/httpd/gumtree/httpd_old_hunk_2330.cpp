            if (!res) {

                res = file_walk(rnew);

            }

        }

        else {

            if ((res = check_symlinks(rnew->filename, ap_allow_options(rnew)))) {

                ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, rnew->server,

                            "Symbolic link not allowed: %s", rnew->filename);

                rnew->status = res;

                return rnew;

            }

            /*

             * do a file_walk, if it doesn't change the per_dir_config then

