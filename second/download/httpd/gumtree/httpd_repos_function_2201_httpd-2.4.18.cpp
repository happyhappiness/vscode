static apr_table_t *get_trailers(h2_task_output *output)
{
    if (!output->trailers_passed) {
        h2_response *response = h2_from_h1_get_response(output->from_h1);
        if (response && response->trailers) {
            output->trailers_passed = 1;
            return response->trailers;
        }
    }
    return NULL;
}