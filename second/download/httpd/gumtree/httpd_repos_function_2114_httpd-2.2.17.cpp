static int invoke_filter_init(request_rec *r, ap_filter_t *filters)
{
    while (filters) {
        if (filters->frec->filter_init_func && filters->r == r) {
            int result = filters->frec->filter_init_func(filters);
            if (result != OK) {
                return result;
            }
        }
        filters = filters->next;
    }
    return OK;
}