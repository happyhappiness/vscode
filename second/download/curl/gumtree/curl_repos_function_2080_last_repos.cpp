static curl_off_t encoder_base64_size(curl_mimepart *part)
{
  curl_off_t size = part->datasize;

  if(size <= 0)
    return size;    /* Unknown size or no data. */

  /* Compute base64 character count. */
  size = 4 * (1 + (size - 1) / 3);

  /* Effective character count must include CRLFs. */
  return size + 2 * ((size - 1) / MAX_ENCODED_LINE_LENGTH);
}