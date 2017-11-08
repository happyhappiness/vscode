static int ap_invoke_filter_init(ap_filter_t *filters)
{
    while (filters) {
        if (filters->frec->filter_init_func) {
            int result = filters->frec->filter_init_func(filters);
            if (result != OK) {
                return result;
            }
        }
        filters = filters->next;
    } 
    return OK;
}