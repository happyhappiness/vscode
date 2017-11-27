static int ntpd_read(void) {
  struct info_kernel *ik;
  int ik_num;
  int ik_size;

  struct info_peer_summary *ps;
  int ps_num;
  int ps_size;

  gauge_t offset_loop;
  gauge_t freq_loop;
  gauge_t offset_error;

  int status;

  /* On Linux, if the STA_NANO bit is set in ik->status, then ik->offset
   * is is nanoseconds, otherwise it's microseconds. */
  double scale_loop = 1e-6;
  double scale_error = 1e-6;

  ik = NULL;
  ik_num = 0;
  ik_size = 0;

  status = ntpd_do_query(REQ_GET_KERNEL, 0, 0, NULL, /* request data */
                         &ik_num, &ik_size,
                         (char **)((void *)&ik), /* response data */
                         sizeof(struct info_kernel));
  if (status != 0) {
    ERROR("ntpd plugin: ntpd_do_query (REQ_GET_KERNEL) failed with status %i",
          status);
    return status;
  } else if ((ik == NULL) || (ik_num == 0) || (ik_size == 0)) {
    ERROR("ntpd plugin: ntpd_do_query returned unexpected data. "
          "(ik = %p; ik_num = %i; ik_size = %i)",
          (void *)ik, ik_num, ik_size);
    return -1;
  }

  if (ntohs(ik->status) & STA_NANO) {
    scale_loop = 1e-9;
    scale_error = 1e-9;
  }

  /* kerninfo -> estimated error */
  offset_loop = (gauge_t)((int32_t)ntohl(ik->offset) * scale_loop);
  freq_loop = ntpd_read_fp(ik->freq);
  offset_error = (gauge_t)((int32_t)ntohl(ik->esterror) * scale_error);

  DEBUG("info_kernel:\n"
        "  pll offset    = %.8g\n"
        "  pll frequency = %.8g\n" /* drift compensation */
        "  est error     = %.8g\n",
        offset_loop, freq_loop, offset_error);

  ntpd_submit("frequency_offset", "loop", freq_loop);
  ntpd_submit("time_offset", "loop", offset_loop);
  ntpd_submit("time_offset", "error", offset_error);

  free(ik);
  ik = NULL;

  status = ntpd_do_query(REQ_PEER_LIST_SUM, 0, 0, NULL, /* request data */
                         &ps_num, &ps_size,
                         (char **)((void *)&ps), /* response data */
                         sizeof(struct info_peer_summary));
  if (status != 0) {
    ERROR(
        "ntpd plugin: ntpd_do_query (REQ_PEER_LIST_SUM) failed with status %i",
        status);
    return status;
  } else if ((ps == NULL) || (ps_num == 0) || (ps_size == 0)) {
    ERROR("ntpd plugin: ntpd_do_query returned unexpected data. "
          "(ps = %p; ps_num = %i; ps_size = %i)",
          (void *)ps, ps_num, ps_size);
    return -1;
  }

  for (int i = 0; i < ps_num; i++) {
    struct info_peer_summary *ptr;
    double offset;

    char peername[NI_MAXHOST];
    uint32_t refclock_id;

    ptr = ps + i;

    status = ntpd_get_name(peername, sizeof(peername), ptr);
    if (status != 0) {
      ERROR("ntpd plugin: Determining name of peer failed.");
      continue;
    }

    refclock_id = ntpd_get_refclock_id(ptr);

    /* Convert the `long floating point' offset value to double */
    M_LFPTOD(ntohl(ptr->offset_int), ntohl(ptr->offset_frc), offset);

    DEBUG("peer %i:\n"
          "  peername   = %s\n"
          "  srcadr     = 0x%08x\n"
          "  reach      = 0%03o\n"
          "  delay      = %f\n"
          "  offset_int = %i\n"
          "  offset_frc = %i\n"
          "  offset     = %f\n"
          "  dispersion = %f\n",
          i, peername, ntohl(ptr->srcadr), ptr->reach, ntpd_read_fp(ptr->delay),
          ntohl(ptr->offset_int), ntohl(ptr->offset_frc), offset,
          ntpd_read_fp(ptr->dispersion));

    if (refclock_id !=
        1) /* not the system clock (offset will always be zero.. */
      ntpd_submit_reach("time_offset", peername, ptr->reach, offset);
    ntpd_submit_reach("time_dispersion", peername, ptr->reach,
                      ntpd_read_fp(ptr->dispersion));
    if (refclock_id == 0) /* not a reference clock */
      ntpd_submit_reach("delay", peername, ptr->reach,
                        ntpd_read_fp(ptr->delay));
  }

  free(ps);
  ps = NULL;

  return 0;
}