static long bio_filter_out_ctrl(BIO *bio, int cmd, long num, void *ptr)
{
    long ret = 1;
    bio_filter_out_ctx_t *outctx = (bio_filter_out_ctx_t *)(bio->ptr);

    switch (cmd) {
    case BIO_CTRL_RESET:
    case BIO_CTRL_EOF:
    case BIO_C_SET_BUF_MEM_EOF_RETURN:
        ap_log_cerror(APLOG_MARK, APLOG_TRACE4, 0, outctx->c,
                      "output bio: unhandled control %d", cmd);
        ret = 0;
        break;
    case BIO_CTRL_WPENDING:
    case BIO_CTRL_PENDING:
    case BIO_CTRL_INFO:
        ret = 0;
        break;
    case BIO_CTRL_GET_CLOSE:
        ret = (long)bio->shutdown;
        break;
      case BIO_CTRL_SET_CLOSE:
        bio->shutdown = (int)num;
        break;
      case BIO_CTRL_FLUSH:
        ret = bio_filter_out_flush(bio);
        break;
      case BIO_CTRL_DUP:
        ret = 1;
        break;
        /* N/A */
      case BIO_C_SET_BUF_MEM:
      case BIO_C_GET_BUF_MEM_PTR:
        /* we don't care */
      case BIO_CTRL_PUSH:
      case BIO_CTRL_POP:
      default:
        ret = 0;
        break;
    }

    return ret;
}