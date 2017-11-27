static int
chrony_request_source_data(int p_src_idx, int *p_is_reachable)
{
  /* Perform Source data request for source #p_src_idx */
  int rc;
  size_t chrony_resp_size;
  tChrony_Request chrony_req;
  tChrony_Response chrony_resp;

  char src_addr[IPV6_STR_MAX_SIZE] = { 0 };

  chrony_init_req(&chrony_req);
  chrony_req.body.source_data.f_index = htonl(p_src_idx);
  rc =
    chrony_query(REQ_SOURCE_DATA, &chrony_req, &chrony_resp,
                 &chrony_resp_size);
  if (rc != 0)
  {
    ERROR(PLUGIN_NAME
          ": chrony_query (REQ_SOURCE_DATA) failed with status %i", rc);
    return rc;
  }

  niptoha(&chrony_resp.body.source_data.addr, src_addr, sizeof(src_addr));
  DEBUG(PLUGIN_NAME
        ": Source[%d] data: .addr = %s, .poll = %u, .stratum = %u, .state = %u, .mode = %u, .flags = %u, .reach = %u, .latest_meas_ago = %u, .orig_latest_meas = %f, .latest_meas = %f, .latest_meas_err = %f",
        p_src_idx, src_addr, ntohs(chrony_resp.body.source_data.f_poll),
        ntohs(chrony_resp.body.source_data.f_stratum),
        ntohs(chrony_resp.body.source_data.f_state),
        ntohs(chrony_resp.body.source_data.f_mode),
        ntohs(chrony_resp.body.source_data.f_flags),
        ntohs(chrony_resp.body.source_data.f_reachability),
        ntohl(chrony_resp.body.source_data.f_since_sample),
        ntohf(chrony_resp.body.source_data.f_origin_latest_meas),
        ntohf(chrony_resp.body.source_data.f_latest_meas),
        ntohf(chrony_resp.body.source_data.f_latest_meas_err));

  /* Push NaN if source is currently not reachable */
  int is_reachable =
    ntohs(chrony_resp.body.source_data.f_reachability) & 0x01;
  *p_is_reachable = is_reachable;

  /* Forward results to collectd-daemon */
  chrony_push_data_valid("clock_stratum", src_addr, is_reachable,
                         ntohs(chrony_resp.body.source_data.f_stratum));
  chrony_push_data_valid("clock_state", src_addr, is_reachable,
                         ntohs(chrony_resp.body.source_data.f_state));
  chrony_push_data_valid("clock_mode", src_addr, is_reachable,
                         ntohs(chrony_resp.body.source_data.f_mode));
  chrony_push_data_valid("clock_reachability", src_addr, is_reachable,
                         ntohs(chrony_resp.body.source_data.f_reachability));
  chrony_push_data_valid("clock_last_meas", src_addr, is_reachable,
                         ntohs(chrony_resp.body.source_data.f_since_sample));

  return CHRONY_RC_OK;
}