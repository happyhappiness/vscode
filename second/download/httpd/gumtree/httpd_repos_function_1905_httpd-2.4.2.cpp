apr_status_t ajp_msg_copy(ajp_msg_t *smsg, ajp_msg_t *dmsg)
{
    if (smsg->len > smsg->max_size) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL, APLOGNO(01082)
                     "ajp_msg_copy(): destination buffer too "
                     "small %" APR_SIZE_T_FMT ", max size is %" APR_SIZE_T_FMT,
                     smsg->len, smsg->max_size);
        return  AJP_ETOSMALL;
    }

    memcpy(dmsg->buf, smsg->buf, smsg->len);
    dmsg->len = smsg->len;
    dmsg->pos = smsg->pos;

    return APR_SUCCESS;
}