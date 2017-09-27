            }
            if (strcmp(user, scratch) != 0) {
                putline(ftemp, line);
                continue;
            }
            else {
                if (!(mask & APHTP_DELUSER)) {
                    /* We found the user we were looking for.
                     * Add him to the file.
                    */
                    apr_file_printf(errfile, "Updating ");
                    putline(ftemp, ctx.out);
                    found++;
                }
                else {
                    /* We found the user we were looking for.
                     * Delete them from the file.
                     */
                    apr_file_printf(errfile, "Deleting ");
                    found++;
                }
            }
        }
        apr_file_close(fpw);
    }
    if (!found && !(mask & APHTP_DELUSER)) {
        apr_file_printf(errfile, "Adding ");
        putline(ftemp, ctx.out);
    }
    else if (!found && (mask & APHTP_DELUSER)) {
        apr_file_printf(errfile, "User %s not found" NL, user);
        exit(0);
    }
    apr_file_printf(errfile, "password for user %s" NL, user);

    /* The temporary file has all the data, just copy it to the new location.
     */
    if (apr_file_copy(dirname, pwfilename, APR_FILE_SOURCE_PERMS, pool) !=
        APR_SUCCESS) {
