static int configured_on_output(request_rec *r, const char *filter_name)
{
    return configured_in_list(r, filter_name, r->output_filters);
}