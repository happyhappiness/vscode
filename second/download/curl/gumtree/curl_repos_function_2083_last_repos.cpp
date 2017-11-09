static curl_off_t encoder_qp_size(curl_mimepart *part)
{
  /* Determining the size can only be done by reading the data: unless the
     data size is 0, we return it as unknown (-1). */
  return part->datasize? -1: 0;
}