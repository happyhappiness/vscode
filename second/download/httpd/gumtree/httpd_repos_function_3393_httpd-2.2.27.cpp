static apr_status_t brigade_flush(apr_vformatter_buff_t *buff)
{
    /* callback function passed to ap_vformatter to be
     * called when vformatter needs to buff and
     * buff.curpos > buff.endpos
     */

    /* "downcast," have really passed a brigade_vprintf_data_t* */
    struct brigade_vprintf_data_t *vd = (struct brigade_vprintf_data_t*)buff;
    apr_status_t res = APR_SUCCESS;

    res = apr_brigade_write(vd->b, *vd->flusher, vd->ctx, vd->cbuff,
                          APR_BUCKET_BUFF_SIZE);

    if(res != APR_SUCCESS) {
      return -1;
    }

    vd->vbuff.curpos = vd->cbuff;
    vd->vbuff.endpos = vd->cbuff + APR_BUCKET_BUFF_SIZE;

    return res;
}