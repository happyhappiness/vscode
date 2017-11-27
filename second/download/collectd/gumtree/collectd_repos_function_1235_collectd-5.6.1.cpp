static int
chrony_request_daemon_stats(void)
{
  /* Perform Tracking request */
  int rc;
  size_t chrony_resp_size;
  tChrony_Request chrony_req;
  tChrony_Response chrony_resp;

  chrony_init_req(&chrony_req);
  rc =
    chrony_query(REQ_TRACKING, &chrony_req, &chrony_resp, &chrony_resp_size);
  if (rc != 0)
  {
    ERROR(PLUGIN_NAME ": chrony_query (REQ_TRACKING) failed with status %i",
          rc);
    return rc;
  }
#if COLLECT_DEBUG
  {
    char src_addr[IPV6_STR_MAX_SIZE] = { 0 };
    niptoha(&chrony_resp.body.tracking.addr, src_addr, sizeof(src_addr));
    DEBUG(PLUGIN_NAME ": Daemon stat: .addr = %s, .ref_id= %u, .stratum = %u, .leap_status = %u, .ref_time = %u:%u:%u, .current_correction = %f, .last_offset = %f, .rms_offset = %f, .freq_ppm = %f, .skew_ppm = %f, .root_delay = %f, .root_dispersion = %f, .last_update_interval = %f", src_addr, ntohs(chrony_resp.body.tracking.f_ref_id),  
          ntohs(chrony_resp.body.tracking.f_stratum),
          ntohs(chrony_resp.body.tracking.f_leap_status),
          ntohl(chrony_resp.body.tracking.f_ref_time.tv_sec_high),
          ntohl(chrony_resp.body.tracking.f_ref_time.tv_sec_low),
          ntohl(chrony_resp.body.tracking.f_ref_time.tv_nsec),
          ntohf(chrony_resp.body.tracking.f_current_correction),
          ntohf(chrony_resp.body.tracking.f_last_offset),
          ntohf(chrony_resp.body.tracking.f_rms_offset),
          ntohf(chrony_resp.body.tracking.f_freq_ppm),
          ntohf(chrony_resp.body.tracking.f_skew_ppm),
          ntohf(chrony_resp.body.tracking.f_root_delay),
          ntohf(chrony_resp.body.tracking.f_root_dispersion),
          ntohf(chrony_resp.body.tracking.f_last_update_interval));
  }
#endif

  double time_ref = ntohl(chrony_resp.body.tracking.f_ref_time.tv_nsec);
  time_ref /= 1000000000.0;
  time_ref += ntohl(chrony_resp.body.tracking.f_ref_time.tv_sec_low);
  if (chrony_resp.body.tracking.f_ref_time.tv_sec_high)
  {
    double secs_high =
      ntohl(chrony_resp.body.tracking.f_ref_time.tv_sec_high);
    secs_high *= 4294967296.0;
    time_ref += secs_high;
  }

  /* Forward results to collectd-daemon */
  /* Type_instance is always 'chrony' to tag daemon-wide data */
  /*                Type                Type_instan  Value */
  chrony_push_data("clock_stratum",     DAEMON_NAME, ntohs(chrony_resp.body.tracking.f_stratum));
  chrony_push_data("time_ref",          DAEMON_NAME, time_ref);  /* unit: s */
  chrony_push_data("time_offset_ntp",   DAEMON_NAME, ntohf(chrony_resp.body.tracking.f_current_correction));      /* Offset between system time and NTP, unit: s */
  chrony_push_data("time_offset",       DAEMON_NAME, ntohf(chrony_resp.body.tracking.f_last_offset)); /* Estimated Offset of the NTP time, unit: s */
  chrony_push_data("time_offset_rms",   DAEMON_NAME, ntohf(chrony_resp.body.tracking.f_rms_offset));  /* averaged value of the above, unit: s */
  chrony_push_data("frequency_error",   DAEMON_NAME, ntohf(chrony_resp.body.tracking.f_freq_ppm));    /* Frequency error of the local osc, unit: ppm */
  chrony_push_data("clock_skew_ppm",    DAEMON_NAME, ntohf(chrony_resp.body.tracking.f_skew_ppm));
  chrony_push_data("root_delay",        DAEMON_NAME, ntohf(chrony_resp.body.tracking.f_root_delay));  /* Network latency between local daemon and the current source */
  chrony_push_data("root_dispersion",   DAEMON_NAME, ntohf(chrony_resp.body.tracking.f_root_dispersion));
  chrony_push_data("clock_last_update", DAEMON_NAME, ntohf(chrony_resp.body.tracking.f_last_update_interval));

  return CHRONY_RC_OK;
}