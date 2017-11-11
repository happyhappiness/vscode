static ap_filter_t *cache_get_filter(ap_filter_t *next, ap_filter_rec_t *rec) {
    while (next) {
        if (next->frec == rec && next->ctx) {
            break;
        }
        next = next->next;
    }
    return next;
}