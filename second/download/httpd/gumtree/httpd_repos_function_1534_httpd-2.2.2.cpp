apr_status_t ajp_msg_serialize_cping(ajp_msg_t *msg)
{
    apr_status_t rc;
    ajp_msg_reset(msg);

    if ((rc = ajp_msg_append_uint8(msg, CMD_AJP13_CPING)) != APR_SUCCESS)
        return rc;

    return APR_SUCCESS;
}