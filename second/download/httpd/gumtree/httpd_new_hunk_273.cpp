        store_variant_list(r, neg);
        res = MULTIPLE_CHOICES;
        goto return_from_multi;
    }

    if (!best) {
        ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
                    "no acceptable variant: %s", r->filename);

        set_neg_headers(r, neg, na_result);
        store_variant_list(r, neg);
        res = NOT_ACCEPTABLE;
        goto return_from_multi;
