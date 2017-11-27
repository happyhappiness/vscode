static int pinba_process_stats_packet (const uint8_t *buffer, /* {{{ */
    size_t buffer_size)
{
  Pinba__Request *request;

  request = pinba__request__unpack (NULL, buffer_size, buffer);

  if (!request)
    return (-1);

  service_process_request(request);
  pinba__request__free_unpacked (request, NULL);

  return (0);
}