static int input_add_header(void *str, const char *key, const char *value)
{
    h2_stream *stream = str;
    apr_status_t status = input_add_data(stream, key, strlen(key), 0);
    if (status == APR_SUCCESS) {
        status = input_add_data(stream, ": ", 2, 0);
        if (status == APR_SUCCESS) {
            status = input_add_data(stream, value, strlen(value), 0);
            if (status == APR_SUCCESS) {
                status = input_add_data(stream, "\r\n", 2, 0);
            }
        }
    }
    return (status == APR_SUCCESS);
}