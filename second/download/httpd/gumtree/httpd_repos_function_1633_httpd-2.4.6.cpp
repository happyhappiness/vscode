static char *get_lines_till_end_token(apr_pool_t * pool,
                                      ap_configfile_t * config_file,
                                      const char *end_token,
                                      const char *begin_token,
                                      const char *where,
                                      apr_array_header_t ** plines)
{
    apr_array_header_t *lines = apr_array_make(pool, 1, sizeof(char *));
    char line[MAX_STRING_LEN];  /* sorry, but this is expected by getline:-( */
    int macro_nesting = 1, any_nesting = 1;
    int line_number_start = config_file->line_number;

    while (!ap_cfg_getline(line, MAX_STRING_LEN, config_file)) {
        char *ptr = line;
        char *first, **new;
        /* skip comments */
        if (*line == '#')
            continue;
        first = ap_getword_conf_nc(pool, &ptr);
        if (first) {
            /* detect nesting... */
            if (!strncmp(first, "</", 2)) {
                any_nesting--;
                if (any_nesting < 0) {
                    ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_WARNING,
                                 0, NULL,
                                 "bad (negative) nesting on line %d of %s",
                                 config_file->line_number - line_number_start,
                                 where);
                }
            }
            else if (!strncmp(first, "<", 1)) {
                any_nesting++;
            }

            if (!strcasecmp(first, end_token)) {
                /* check for proper closing */
                char * endp = (char *) ap_strrchr_c(line, '>');

                /* this cannot happen if end_token contains '>' */
                if (endp == NULL) {
                  return "end directive missing closing '>'";
                }

                warn_if_non_blank(
                    "non blank chars found after directive closing",
                    endp+1, config_file);

                macro_nesting--;
                if (!macro_nesting) {
                    if (any_nesting) {
                        ap_log_error(APLOG_MARK,
                                     APLOG_NOERRNO | APLOG_WARNING, 0, NULL,
                                     "bad cumulated nesting (%+d) in %s",
                                     any_nesting, where);
                    }
                    *plines = lines;
                    return NULL;
                }
            }
            else if (begin_token && !strcasecmp(first, begin_token)) {
                macro_nesting++;
            }
        }
        new = apr_array_push(lines);
        *new = apr_psprintf(pool, "%s" APR_EOL_STR, line); /* put EOL back? */
    }

    return apr_psprintf(pool, "expected token not found: %s", end_token);
}