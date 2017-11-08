int Curl_digest_final(digest_context *context, unsigned char *result)
{
  (*context->digest_hash->digest_final)(result, context->digest_hashctx);

  free(context->digest_hashctx);
  free(context);

  return 0;
}