static int configured_on_input(request_rec *r, const char *filter_name)
{
    return configured_in_list(r, filter_name, r->input_filters);
}