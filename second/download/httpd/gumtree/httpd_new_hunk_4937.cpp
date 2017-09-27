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
