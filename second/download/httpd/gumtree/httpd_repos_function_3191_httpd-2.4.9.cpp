static int do_errorlog_format(apr_array_header_t *fmt, ap_errorlog_info *info,
                              char *buf, int buflen, int *errstr_start,
                              int *errstr_end, const char *err_fmt, va_list args)
{
#ifndef AP_UNSAFE_ERROR_LOG_UNESCAPED
    char scratch[MAX_STRING_LEN];
#endif
    int i;
    int len = 0;
    int field_start = 0;
    int skipping = 0;
    ap_errorlog_format_item *items = (ap_errorlog_format_item *)fmt->elts;

    AP_DEBUG_ASSERT(fmt->nelts > 0);
    for (i = 0; i < fmt->nelts; ++i) {
        ap_errorlog_format_item *item = &items[i];
        if (item->flags & AP_ERRORLOG_FLAG_FIELD_SEP) {
            if (skipping) {
                skipping = 0;
            }
            else {
                field_start = len;
            }
        }

        if (item->flags & AP_ERRORLOG_FLAG_MESSAGE) {
            /* the actual error message */
            *errstr_start = len;
#ifndef AP_UNSAFE_ERROR_LOG_UNESCAPED
            if (apr_vsnprintf(scratch, MAX_STRING_LEN, err_fmt, args)) {
                len += ap_escape_errorlog_item(buf + len, scratch,
                                               buflen - len);

            }
#else
            len += apr_vsnprintf(buf + len, buflen - len, err_fmt, args);
#endif
            *errstr_end = len;
        }
        else if (skipping) {
            continue;
        }
        else if (info->level != -1 && (int)item->min_loglevel > info->level) {
            len = field_start;
            skipping = 1;
        }
        else {
            int item_len = (*item->func)(info, item->arg, buf + len,
                                         buflen - len);
            if (!item_len) {
                if (item->flags & AP_ERRORLOG_FLAG_REQUIRED) {
                    /* required item is empty. skip whole line */
                    buf[0] = '\0';
                    return 0;
                }
                else if (item->flags & AP_ERRORLOG_FLAG_NULL_AS_HYPHEN) {
                    buf[len++] = '-';
                }
                else {
                    len = field_start;
                    skipping = 1;
                }
            }
            else {
                len += item_len;
            }
        }
    }
    return len;
}