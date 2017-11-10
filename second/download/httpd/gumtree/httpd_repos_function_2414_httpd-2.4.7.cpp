static int configured_in_list(request_rec *r, const char *filter_name,
                              struct ap_filter_t *filter_list)
{
    struct ap_filter_t *filter = filter_list;

    while (filter) {
        if (!strcasecmp(filter_name, filter->frec->name)) {
            return 1;
        }
        filter = filter->next;
    }
    return 0;
}