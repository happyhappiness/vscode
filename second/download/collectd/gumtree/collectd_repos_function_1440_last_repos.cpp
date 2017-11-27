static int dns_run_pcap_loop(void) {
  pcap_t *pcap_obj;
  char pcap_error[PCAP_ERRBUF_SIZE];
  struct bpf_program fp = {0};

  int status;

  /* Don't block any signals */
  {
    sigset_t sigmask;
    sigemptyset(&sigmask);
    pthread_sigmask(SIG_SETMASK, &sigmask, NULL);
  }

  /* Passing `pcap_device == NULL' is okay and the same as passign "any" */
  DEBUG("dns plugin: Creating PCAP object..");
  pcap_obj = pcap_open_live((pcap_device != NULL) ? pcap_device : "any",
                            PCAP_SNAPLEN, 0 /* Not promiscuous */,
                            (int)CDTIME_T_TO_MS(plugin_get_interval() / 2),
                            pcap_error);
  if (pcap_obj == NULL) {
    ERROR("dns plugin: Opening interface `%s' "
          "failed: %s",
          (pcap_device != NULL) ? pcap_device : "any", pcap_error);
    return PCAP_ERROR;
  }

  status = pcap_compile(pcap_obj, &fp, "udp port 53", 1, 0);
  if (status < 0) {
    ERROR("dns plugin: pcap_compile failed: %s", pcap_statustostr(status));
    return status;
  }

  status = pcap_setfilter(pcap_obj, &fp);
  if (status < 0) {
    ERROR("dns plugin: pcap_setfilter failed: %s", pcap_statustostr(status));
    return status;
  }

  DEBUG("dns plugin: PCAP object created.");

  dnstop_set_pcap_obj(pcap_obj);
  dnstop_set_callback(dns_child_callback);

  status = pcap_loop(pcap_obj, -1 /* loop forever */,
                     handle_pcap /* callback */, NULL /* user data */);
  INFO("dns plugin: pcap_loop exited with status %i.", status);
  /* We need to handle "PCAP_ERROR" specially because libpcap currently
   * doesn't return PCAP_ERROR_IFACE_NOT_UP for compatibility reasons. */
  if (status == PCAP_ERROR)
    status = PCAP_ERROR_IFACE_NOT_UP;

  pcap_close(pcap_obj);
  return status;
}