            }
            if (strcmp(user, scratch) != 0) {
                putline(ftemp, line);
                continue;
            }
            else {
                /* We found the user we were looking for */
                found++;
                if ((mask & APHTP_DELUSER)) {
                    /* Delete entry from the file */
                    apr_file_printf(errfile, "Deleting ");
                }
                else if ((mask & APHTP_VERIFY)) {
                    /* Verify */
                    char *hash = colon + 1;
                    size_t len;

                    len = strcspn(hash, "\r\n");
                    if (len == 0) {
                        apr_file_printf(errfile, "Empty hash for user %s" NL,
                                        user);
                        exit(ERR_INVALID);
                    }
                    hash[len] = '\0';

                    i = verify(&ctx, hash);
                    if (i != 0) {
                        apr_file_printf(errfile, "%s" NL, ctx.errstr);
                        exit(i);
                    }
                }
                else {
                    /* Update entry */
                    apr_file_printf(errfile, "Updating ");
                    putline(ftemp, ctx.out);
                }
            }
        }
        apr_file_close(fpw);
    }
    if (!found) {
        if (mask & APHTP_DELUSER) {
            apr_file_printf(errfile, "User %s not found" NL, user);
            exit(0);
        }
        else if (mask & APHTP_VERIFY) {
            apr_file_printf(errfile, "User %s not found" NL, user);
            exit(ERR_BADUSER);
        }
        else {
            apr_file_printf(errfile, "Adding ");
            putline(ftemp, ctx.out);
        }
    }
    if (mask & APHTP_VERIFY) {
        apr_file_printf(errfile, "Password for user %s correct." NL, user);
        exit(0);
    }

    apr_file_printf(errfile, "password for user %s" NL, user);

    /* The temporary file has all the data, just copy it to the new location.
     */
    if (apr_file_copy(dirname, pwfilename, APR_FILE_SOURCE_PERMS, pool) !=
        APR_SUCCESS) {
