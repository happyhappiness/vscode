static int snprintf_flush(apr_vformatter_buff_t *vbuff)
{
    /* if the buffer fills we have to abort immediately, there is no way
     * to "flush" an apr_snprintf... there's nowhere to flush it to.
     */
    return -1;
}