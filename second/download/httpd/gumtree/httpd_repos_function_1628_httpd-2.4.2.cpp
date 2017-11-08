static void update_r_in_filters(ap_filter_t *f,
                                request_rec *from,
                                request_rec *to)
{
    while (f) {
        if (f->r == from) {
            f->r = to;
        }
        f = f->next;
    }
}