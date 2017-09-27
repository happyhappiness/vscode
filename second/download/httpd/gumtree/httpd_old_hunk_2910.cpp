            continue;
        }

        /* if we get here, the main entry rule was a match */
        /* this will be the last run through the loop */
#if MIME_MAGIC_DEBUG
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                    MODNAME ": rule matched, line=%d type=%d %s",
                    m->lineno, m->type,
                    (m->type == STRING) ? m->value.s : "");
#endif

        /* print the match */
