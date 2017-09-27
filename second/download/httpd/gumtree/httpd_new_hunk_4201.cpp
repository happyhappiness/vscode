        else {
            ++total;
        }
    }
    p += apr_snprintf(p, sizeof(buf) - (p - buf), " %ux%u",
                      total, count[IPHASH_TABLE_SIZE - 1]);
    /* Intentional no APLOGNO */
    /* buf provides APLOGNO */
    ap_log_error(APLOG_MARK, APLOG_DEBUG, main_s, buf);
}
#endif


/* This hashing function is designed to get good distribution in the cases
