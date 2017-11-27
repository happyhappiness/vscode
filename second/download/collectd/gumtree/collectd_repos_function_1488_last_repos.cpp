static notification_t c_ipmi_notification_init(c_ipmi_instance_t const *st,
                                               int severity) {
  notification_t n = {severity, cdtime(), "", "", "ipmi", "", "", "", NULL};

  sstrncpy(n.host, (st->host != NULL) ? st->host : hostname_g, sizeof(n.host));
  return n;
}