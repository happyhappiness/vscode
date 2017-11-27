static int iptables_read(void) {
  int num_failures = 0;
  ip_chain_t *chain;

  /* Init the iptc handle structure and query the correct table */
  for (int i = 0; i < chain_num; i++) {
    chain = chain_list[i];

    if (!chain) {
      DEBUG("iptables plugin: chain == NULL");
      continue;
    }

    if (chain->ip_version == IPV4) {
#ifdef HAVE_IPTC_HANDLE_T
      iptc_handle_t _handle;
      iptc_handle_t *handle = &_handle;

      *handle = iptc_init(chain->table);
#else
      iptc_handle_t *handle;
      handle = iptc_init(chain->table);
#endif

      if (!handle) {
        ERROR("iptables plugin: iptc_init (%s) failed: %s", chain->table,
              iptc_strerror(errno));
        num_failures++;
        continue;
      }

      submit_chain(handle, chain);
      iptc_free(handle);
    } else if (chain->ip_version == IPV6) {
#ifdef HAVE_IP6TC_HANDLE_T
      ip6tc_handle_t _handle;
      ip6tc_handle_t *handle = &_handle;

      *handle = ip6tc_init(chain->table);
#else
      ip6tc_handle_t *handle;
      handle = ip6tc_init(chain->table);
#endif
      if (!handle) {
        ERROR("iptables plugin: ip6tc_init (%s) failed: %s", chain->table,
              ip6tc_strerror(errno));
        num_failures++;
        continue;
      }

      submit6_chain(handle, chain);
      ip6tc_free(handle);
    } else
      num_failures++;
  } /* for (i = 0 .. chain_num) */

  return (num_failures < chain_num) ? 0 : -1;
}