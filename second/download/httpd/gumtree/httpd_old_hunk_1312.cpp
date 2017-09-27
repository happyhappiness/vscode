    *indexes = apr_array_make(r->pool, ranges, sizeof(indexes_t));
    while ((cur = ap_getword(r->pool, &range, ','))) {
        char *dash;
        char *errp;
        apr_off_t number, start, end;

        if (!(dash = strchr(cur, '-'))) {
            break;
        }

        if (dash == range) {
            /* In the form "-5" */
            if (apr_strtoff(&number, dash+1, &errp, 10) || *errp) {
                break;
            }
            start = clength - number;
            end = clength - 1;
        }
        else {
            *dash++ = '\0';
            if (apr_strtoff(&number, cur, &errp, 10) || *errp) {
                break;
            }
            start = number;
            if (*dash) {
                if (apr_strtoff(&number, dash, &errp, 10) || *errp) {
                    break;
                }
                end = number;
            }
            else {                  /* "5-" */
                end = clength - 1;
            }
        }

        if (start < 0) {
            start = 0;
        }
        if (end >= clength) {
            end = clength - 1;
        }

        if (start > end) {
            /* ignore? count? */
            break;
        }

        idx = (indexes_t *)apr_array_push(*indexes);
        idx->start = start;
        idx->end = end;
        sum_lengths += end - start + 1;
        /* new set again */
        num_ranges++;
    }

    if (sum_lengths >= clength) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "Sum of ranges not smaller than file, ignoring.");
        return 0;
    }

