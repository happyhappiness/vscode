static int
chrony_request_sources_count(unsigned int *p_count)
{
  /* Requests the number of time sources from the chrony daemon */
  int rc;
  size_t chrony_resp_size;
  tChrony_Request chrony_req;
  tChrony_Response chrony_resp;

  DEBUG(PLUGIN_NAME ": Requesting data");
  chrony_init_req(&chrony_req);
  rc =
    chrony_query(REQ_N_SOURCES, &chrony_req, &chrony_resp, &chrony_resp_size);
  if (rc != 0)
  {
    ERROR(PLUGIN_NAME ": chrony_query (REQ_N_SOURCES) failed with status %i",
          rc);
    return rc;
  }

  *p_count = ntohl(chrony_resp.body.n_sources.f_n_sources);
  DEBUG(PLUGIN_NAME ": Getting data of %d clock sources", *p_count);

  return CHRONY_RC_OK;
}