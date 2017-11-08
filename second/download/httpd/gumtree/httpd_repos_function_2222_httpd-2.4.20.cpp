void h2_response_set_trailers(h2_response *response, apr_table_t *trailers)
{
    response->trailers = trailers;
}