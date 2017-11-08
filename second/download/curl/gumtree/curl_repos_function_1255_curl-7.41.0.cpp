int Curl_MD5_final(MD5_context *context, unsigned char *result)
{
  (*context->md5_hash->md5_final_func)(result, context->md5_hashctx);

  free(context->md5_hashctx);
  free(context);

  return 0;
}