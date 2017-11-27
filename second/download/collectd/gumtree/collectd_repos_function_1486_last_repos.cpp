static void c_ipmi_error(c_ipmi_instance_t *st, const char *func, int status) {
  char errbuf[ERR_BUF_SIZE] = {0};

  if (IPMI_IS_OS_ERR(status) || IPMI_IS_RMCPP_ERR(status) ||
      IPMI_IS_IPMI_ERR(status)) {
    ipmi_get_error_string(status, errbuf, sizeof(errbuf));
  }

  if (errbuf[0] == 0) {
    snprintf(errbuf, sizeof(errbuf), "Unknown error %#x", status);
  }
  errbuf[sizeof(errbuf) - 1] = 0;

  ERROR("ipmi plugin: %s failed for `%s`: %s", func, st->name, errbuf);
}