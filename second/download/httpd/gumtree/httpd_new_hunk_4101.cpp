            count = AJP_MAX_BUFFER_SZ;
        }
        rc = ajp_msg_dump(r->pool, msg, err, count, &buf);
        if (rc == APR_SUCCESS) {
            while ((next = ap_strchr(buf, '\n'))) {
                *next = '\0';
                /* Intentional no APLOGNO */
                ap_log_rerror(APLOG_MARK, level, 0, r, "%s", buf);
                buf = next + 1;
            }
            /* Intentional no APLOGNO */
            ap_log_rerror(APLOG_MARK, level, 0, r, "%s", buf);
        }
    }
    return rc;
}

