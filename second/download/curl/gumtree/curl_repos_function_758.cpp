CURLcode convert_to_network(char *buffer, size_t length)
{
  /* translate from the host encoding to the network encoding */
  char *input_ptr, *output_ptr;
  size_t res, in_bytes, out_bytes;

  /* open an iconv conversion descriptor if necessary */
  if(outbound_cd == (iconv_t)-1) {
    outbound_cd = iconv_open(CURL_ICONV_CODESET_OF_NETWORK,
                             CURL_ICONV_CODESET_OF_HOST);
    if(outbound_cd == (iconv_t)-1) {
      return CURLE_CONV_FAILED;
    }
  }
  /* call iconv */
  input_ptr = output_ptr = buffer;
  in_bytes = out_bytes = length;
  res = iconv(outbound_cd, &input_ptr,  &in_bytes,
              &output_ptr, &out_bytes);
  if((res == (size_t)-1) || (in_bytes != 0)) {
    return CURLE_CONV_FAILED;
  }

  return CURLE_OK;
}