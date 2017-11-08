static void *create_buffer_config(apr_pool_t *p, char *dummy)
{
    buffer_conf *new = (buffer_conf *) apr_pcalloc(p, sizeof(buffer_conf));

    new->size_set = 0; /* unset */
    new->size = DEFAULT_BUFFER_SIZE; /* default size */

    return (void *) new;
}