        store_variant_list(r, neg);
        res = MULTIPLE_CHOICES;
        goto return_from_multi;
    }

    if (!best) {
        ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
                    "no acceptable variant: %s", r->filename);

        set_neg_headers(r, neg, na_result);
        store_variant_list(r, neg);
        res = NOT_ACCEPTABLE;
        goto return_from_multi;
-- apache_1.3.1/src/modules/standard/mod_rewrite.c	1998-07-18 23:30:46.000000000 +0800
