int Curl_MD5_update(MD5_context *context,
                    const unsigned char *data,
                    unsigned int len)
{
  (*context->md5_hash->md5_update_func)(context->md5_hashctx, data, len);

  return 0;
}