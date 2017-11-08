static long bio_bucket_ctrl(BIO *bio, int cmd, long num, void *ptr)
{
    long ret = 1;
    char **pptr;

    BIO_bucket_t *b = BIO_bucket_ptr(bio);

    switch (cmd) {
      case BIO_CTRL_RESET:
        b->blen = b->length = 0;
        break;
      case BIO_CTRL_EOF:
        ret = (long)((b->blen + b->length) == 0);
        break;
      case BIO_C_SET_BUF_MEM_EOF_RETURN:
        b->blen = b->length = (apr_size_t)num;
        break;
      case BIO_CTRL_INFO:
        ret = (long)(b->blen + b->length);
        if (ptr) {
            pptr = (char **)ptr;
            *pptr = (char *)&(b->buffer[0]);
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
        ret = (long)(b->blen + b->length);
        break;
      case BIO_CTRL_FLUSH:
        ret = (BIO_bucket_flush(bio) == APR_SUCCESS);
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