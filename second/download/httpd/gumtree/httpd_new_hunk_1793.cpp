                RAND_seed(stackdata+n, 128);
                nDone += 128;

            }
        }
    }
    ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, s,
                 "%sSeeding PRNG with %d bytes of entropy", prefix, nDone);

    if (RAND_status() == 0)
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                     "%sPRNG still contains insufficient entropy!", prefix);

