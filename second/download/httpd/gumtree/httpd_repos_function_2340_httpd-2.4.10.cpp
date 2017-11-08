static int request_is_filter_present(request_rec * r, ap_filter_rec_t *fn)
{
    ap_filter_t * f = r->input_filters;
    while (f) {
        if (f->frec == fn) {
            return 1;
        }
        f = f->next;
    }
    return 0;
}