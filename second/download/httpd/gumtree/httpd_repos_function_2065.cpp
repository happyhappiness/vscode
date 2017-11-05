static void ap_request_remove_filter(request_rec * r)
{
    ap_filter_t * f = r->input_filters;
    while (f) {
        if (f->frec->filter_func.in_func == kept_body_filter ||
                f->frec->filter_func.in_func == keep_body_filter) {
            ap_remove_input_filter(f);
        }
        f = f->next;
    }
}