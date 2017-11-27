static void c_ipmi_log(os_handler_t *handler, const char *format,
                       enum ipmi_log_type_e log_type, va_list ap) {
  char msg[ERR_BUF_SIZE];

  vsnprintf(msg, sizeof(msg), format, ap);

  switch (log_type) {
  case IPMI_LOG_INFO:
    INFO("ipmi plugin: %s", msg);
    break;
  case IPMI_LOG_WARNING:
    NOTICE("ipmi plugin: %s", msg);
    break;
  case IPMI_LOG_SEVERE:
    WARNING("ipmi plugin: %s", msg);
    break;
  case IPMI_LOG_FATAL:
    ERROR("ipmi plugin: %s", msg);
    break;
  case IPMI_LOG_ERR_INFO:
    ERROR("ipmi plugin: %s", msg);
    break;
#if COLLECT_DEBUG
  case IPMI_LOG_DEBUG_START:
  case IPMI_LOG_DEBUG:
    DEBUG("ipmi plugin: %s", msg);
    break;
  case IPMI_LOG_DEBUG_CONT:
  case IPMI_LOG_DEBUG_END:
    DEBUG("%s", msg);
    break;
#else
  case IPMI_LOG_DEBUG_START:
  case IPMI_LOG_DEBUG:
  case IPMI_LOG_DEBUG_CONT:
  case IPMI_LOG_DEBUG_END:
    break;
#endif
  }
}