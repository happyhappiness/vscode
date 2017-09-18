    }
    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
                 "%sSeeding PRNG with %d bytes of entropy", prefix, nDone);

    if (RAND_status() == 0)
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                     "%sPRNG still contains insufficient entropy!", prefix);

    return nDone;
}

#define BUFSIZE 8192

