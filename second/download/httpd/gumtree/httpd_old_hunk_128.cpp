        /*
         * Do symlink checks first, because they are done with the
         * permissions appropriate to the *parent* directory...
         */

        if ((res = check_symlinks(test_dirname, core_dir->opts))) {
            ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
                        "Symbolic link not allowed: %s", test_dirname);
            return res;
        }

        /*
         * Begin *this* level by looking for matching <Directory> sections
