static void remove_reqtimeout(ap_filter_t *next)
{
    ap_filter_t *reqto = NULL;
    ap_filter_rec_t *filter;

    filter = ap_get_input_filter_handle("reqtimeout");
    if (!filter) {
        return;
    }

    while (next) {
        if (next->frec == filter) {
            reqto = next;
            break;
        }
        next = next->next;
    }
    if (reqto) {
        ap_remove_input_filter(reqto);
    }
}