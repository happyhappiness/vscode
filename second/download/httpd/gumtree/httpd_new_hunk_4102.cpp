
    return APR_SUCCESS;
}

static APR_INLINE int ajp_log_overflow(ajp_msg_t *msg, const char *context)
{
    ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL, APLOGNO(03229)
                 "%s(): BufferOverflowException %" APR_SIZE_T_FMT
                 " %" APR_SIZE_T_FMT,
                 context, msg->pos, msg->len);
    return AJP_EOVERFLOW;
}

