int Curl_digest_update(digest_context *context,
                       const unsigned char *data,
                       unsigned int len)
{
  (*context->digest_hash->digest_update)(context->digest_hashctx, data, len);

  return 0;
}