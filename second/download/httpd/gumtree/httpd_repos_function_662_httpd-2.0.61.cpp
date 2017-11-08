static long bio_filter_out_ctrl(BIO *bio, int cmd, long num, void *ptr)
{
    long ret = 1;
    char **pptr;

    bio_filter_out_ctx_t *outctx = (bio_filter_out_ctx_t *)(bio->ptr);

    switch (cmd) {
      case BIO_CTRL_RESET:
        outctx->blen = outctx->length = 0;
        break;
      case BIO_CTRL_EOF:
        ret = (long)((outctx->blen + outctx->length) == 0);
        break;
      case BIO_C_SET_BUF_MEM_EOF_RETURN:
        outctx->blen = outctx->length = (apr_size_t)num;
        break;
      case BIO_CTRL_INFO:
        ret = (long)(outctx->blen + outctx->length);
        if (ptr) {
            pptr = (char **)ptr;
            *pptr = (char *)&(outctx->buffer[0]);
        }
        break;
      case BIO_CTRL_GET_CLOSE:
        ret = (long)bio->shutdown;
        break;
      case BIO_CTRL_SET_CLOSE:
        bio->shutdown = (int)num;
        break;
      case BIO_CTRL_WPENDING:
        ret = 0L;
        break;
      case BIO_CTRL_PENDING:
        ret = (long)(outctx->blen + outctx->length);
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