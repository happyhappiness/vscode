    }

    if (ccfg->min_rate > 0 && rv == APR_SUCCESS) {
        extend_timeout(ccfg, bb);
    }

    if (APR_STATUS_IS_TIMEUP(rv)) {
        ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, f->c,
                      "Request %s read timeout", ccfg->type);
    }
    return rv;
}

