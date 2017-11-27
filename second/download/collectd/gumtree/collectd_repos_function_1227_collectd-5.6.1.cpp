static int
chrony_recv_response(tChrony_Response * p_resp, size_t p_resp_max_size,
                     size_t * p_resp_size)
{
  ssize_t rc = recv(g_chrony_socket, p_resp, p_resp_max_size, 0);
  if (rc <= 0)
  {
    ERROR(PLUGIN_NAME ": Error receiving packet: %s (%d)", strerror(errno),
          errno);
    return CHRONY_RC_FAIL;
  }
  else
  {
    *p_resp_size = rc;
    return CHRONY_RC_OK;
  }
}