 * @param smsg      source AJP message
 * @param dmsg      destination AJP message
 * @return          APR_SUCCESS or error
 */
apr_status_t ajp_msg_copy(ajp_msg_t *smsg, ajp_msg_t *dmsg)
{
    if (dmsg == NULL) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
                     "ajp_msg_copy(): destination msg is null");
        return AJP_EINVAL;
    }

    if (smsg->len > smsg->max_size) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
                     "ajp_msg_copy(): destination buffer too "
                     "small %" APR_SIZE_T_FMT ", max size is %" APR_SIZE_T_FMT,
                     smsg->len, smsg->max_size);
        return  AJP_ETOSMALL;
    }

