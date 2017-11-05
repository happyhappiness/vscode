static int cache_replace_filter(ap_filter_t *next, ap_filter_rec_t *from,
        ap_filter_rec_t *to) {
    ap_filter_t *ffrom = NULL, *fto = NULL;
    while (next) {
        if (next->frec == from && !next->ctx) {
            ffrom = next;
        }
        if (next->frec == to && !next->ctx) {
            fto = next;
        }
        next = next->next;
    }
    if (ffrom && fto) {
        ffrom->frec = fto->frec;
        ffrom->ctx = fto->ctx;
        ap_remove_output_filter(fto);
        return 1;
    }
    if (ffrom) {
        ap_remove_output_filter(ffrom);
    }
    return 0;
}