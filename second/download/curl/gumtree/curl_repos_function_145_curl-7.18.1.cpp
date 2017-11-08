int
Curl_inet_ntoa_r_a(struct in_addr internet_address,
                   char * output_buffer, int output_buffer_length)

{
  int rc;
  int i;
  char * cp;

  if (!output_buffer || output_buffer_length < 16)
    return inet_ntoa_r(internet_address, output_buffer, output_buffer_length);

  if (!(cp = malloc(output_buffer_length + 1)))
    return -1;

  rc = inet_ntoa_r(internet_address, cp, output_buffer_length);

  if (rc) {
    free(cp);
    return rc;
    }

  cp[output_buffer_length - 1] = '\0';
  i = strlen(cp);
  QadrtConvertE2A(output_buffer, cp, i, i);
  output_buffer[i] = '\0';
  free(cp);
  return rc;
}