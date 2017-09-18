             * See if this is our user.
             */
            colon = strchr(scratch, ':');
            if (colon != NULL) {
                *colon = '\0';
            }
            if (strcmp(user, scratch) != 0) {
                putline(ftemp, line);
                continue;
            }
            else {
                /* We found the user we were looking for, add him to the file.
                 */
                apr_file_printf(errfile, "Updating ");
                putline(ftemp, record);
                found++;
            }
        }
        apr_file_close(fpw);
    }
    if (!found) {
        apr_file_printf(errfile, "Adding ");
        putline(ftemp, record);
    }
    apr_file_printf(errfile, "password for user %s\n", user);

    /* The temporary file has all the data, just copy it to the new location.
     */
    if (apr_file_copy(tn, pwfilename, APR_FILE_SOURCE_PERMS, pool) !=
        APR_SUCCESS) {
