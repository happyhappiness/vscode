static int
chrony_request_source_stats(int p_src_idx, const int *p_is_reachable)
{
  /* Perform Source stats request for source #p_src_idx */
  int rc;
  size_t chrony_resp_size;
  tChrony_Request chrony_req;
  tChrony_Response chrony_resp;
  double skew_ppm, frequency_error, time_offset;

  char src_addr[IPV6_STR_MAX_SIZE] = { 0 };

  if (*p_is_reachable == 0)
  {
    skew_ppm = 0;
    frequency_error = 0;
    time_offset = 0;
  }
  else
  {
    chrony_init_req(&chrony_req);
    chrony_req.body.source_stats.f_index = htonl(p_src_idx);
    rc =
      chrony_query(REQ_SOURCE_STATS, &chrony_req, &chrony_resp,
                   &chrony_resp_size);
    if (rc != 0)
    {
      ERROR(PLUGIN_NAME
            ": chrony_query (REQ_SOURCE_STATS) failed with status %i", rc);
      return rc;
    }

    skew_ppm = ntohf(chrony_resp.body.source_stats.f_skew_ppm);
    frequency_error =
      ntohf(chrony_resp.body.source_stats.f_rtc_gain_rate_ppm);
    time_offset = ntohf(chrony_resp.body.source_stats.f_est_offset);

    niptoha(&chrony_resp.body.source_stats.addr, src_addr, sizeof(src_addr));
    DEBUG(PLUGIN_NAME
          ": Source[%d] stat: .addr = %s, .ref_id= %u, .n_samples = %u, "
          ".n_runs = %u, .span_seconds = %u, .rtc_seconds_fast = %f, "
          ".rtc_gain_rate_ppm = %f, .skew_ppm= %f, .est_offset = %f, .est_offset_err = %f",
          p_src_idx, src_addr,
          ntohl(chrony_resp.body.source_stats.f_ref_id),
          ntohl(chrony_resp.body.source_stats.f_n_samples),
          ntohl(chrony_resp.body.source_stats.f_n_runs),
          ntohl(chrony_resp.body.source_stats.f_span_seconds),
          ntohf(chrony_resp.body.source_stats.f_rtc_seconds_fast),
          frequency_error, skew_ppm, time_offset,
          ntohf(chrony_resp.body.source_stats.f_est_offset_err));

  } /* if (*is_reachable) */

  /* Forward results to collectd-daemon */
  chrony_push_data_valid("clock_skew_ppm", src_addr, *p_is_reachable, skew_ppm);
  chrony_push_data_valid("frequency_error", src_addr, *p_is_reachable, frequency_error); /* unit: ppm */
  chrony_push_data_valid("time_offset", src_addr, *p_is_reachable, time_offset);         /* unit: s */

  return CHRONY_RC_OK;
}