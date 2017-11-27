static int
chrony_send_request(const tChrony_Request * p_req, size_t p_req_size)
{
  if (send(g_chrony_socket, p_req, p_req_size, 0) < 0)
  {
    ERROR(PLUGIN_NAME ": Error sending packet. Errno = %d", errno);
    return CHRONY_RC_FAIL;
  }
  return CHRONY_RC_OK;
}