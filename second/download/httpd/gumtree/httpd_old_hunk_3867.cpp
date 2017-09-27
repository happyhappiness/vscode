
        /* Count our log entries */
        entries++;

        /* Check if this could even be an IP address */
        if (!apr_isxdigit(line[0]) && line[0] != ':') {
                withname++;
            apr_file_puts(line, outfile);
            continue;
        }

        /* Terminate the line at the next space */
        if ((space = strchr(line, ' ')) != NULL) {
