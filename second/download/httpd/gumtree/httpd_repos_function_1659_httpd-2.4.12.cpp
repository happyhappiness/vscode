static apr_status_t array_close(void *param)
{
    array_contents_t *ml = (array_contents_t *) param;
    /* move index at end of stream... */
    ml->index = ml->contents->nelts;
    ml->char_index = ml->length;
    return APR_SUCCESS;
}