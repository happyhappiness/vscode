static void submit_chain(iptc_handle_t *handle, ip_chain_t *chain) {
  const struct ipt_entry *entry;
  int rule_num;

  /* Find first rule for chain and use the iterate macro */
  entry = iptc_first_rule(chain->chain, handle);
  if (entry == NULL) {
    DEBUG("iptc_first_rule failed: %s", iptc_strerror(errno));
    return;
  }

  rule_num = 1;
  while (entry) {
    if (chain->rule_type == RTYPE_NUM) {
      submit_match(NULL, entry, chain, rule_num);
    } else {
      IPT_MATCH_ITERATE(entry, submit_match, entry, chain, rule_num);
    }

    entry = iptc_next_rule(entry, handle);
    rule_num++;
  } /* while (entry) */
}