                            argv[0], pwfilename);
            exit(ERR_FILEPERM);
        }
        while (apr_file_gets(line, sizeof(line), fpw) == APR_SUCCESS) {
            char *colon;

            strcpy(cp, line);
            scratch = cp;
            while (apr_isspace(*scratch)) {
                ++scratch;
            }

            if (!*scratch || (*scratch == '#')) {
                putline(ftemp, line);
                continue;
            }
            /*
             * See if this is our user.
             */
            colon = strchr(scratch, ':');
            if (colon != NULL) {
                *colon = '\0';
            }
            else {
                /*
                 * If we've not got a colon on the line, this could well 
                 * not be a valid htpasswd file.
                 * We should bail at this point.
                 */
                apr_file_printf(errfile, "\n%s: The file %s does not appear "
                                         "to be a valid htpasswd file.\n",
                                argv[0], pwfilename);
                apr_file_close(fpw);
                exit(ERR_INVALID);
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
                    putline(ftemp, record);
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
        putline(ftemp, record);
    }
    else if (!found && (mask & APHTP_DELUSER)) {
        apr_file_printf(errfile, "User %s not found\n", user);
        exit(0);
    }
    apr_file_printf(errfile, "password for user %s\n", user);

    /* The temporary file has all the data, just copy it to the new location.
     */
    if (apr_file_copy(dirname, pwfilename, APR_FILE_SOURCE_PERMS, pool) !=
        APR_SUCCESS) {
        apr_file_printf(errfile, "%s: unable to update file %s\n", 
                        argv[0], pwfilename);
        exit(ERR_FILEPERM);
    }
    apr_file_close(ftemp);
