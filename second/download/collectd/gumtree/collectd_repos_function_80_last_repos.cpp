static void domain_state_submit(virDomainPtr dom, int state, int reason) {

  if ((state < 0) || (state >= STATIC_ARRAY_SIZE(domain_states))) {
    ERROR(PLUGIN_NAME ": Array index out of bounds: state=%d", state);
    return;
  }

  char msg[DATA_MAX_NAME_LEN];
  const char *state_str = domain_states[state];
#ifdef HAVE_DOM_REASON
  if ((reason < 0) || (reason >= STATIC_ARRAY_SIZE(domain_reasons[0]))) {
    ERROR(PLUGIN_NAME ": Array index out of bounds: reason=%d", reason);
    return;
  }

  const char *reason_str = domain_reasons[state][reason];
  /* Array size for domain reasons is fixed, but different domain states can
   * have different number of reasons. We need to check if reason was
   * successfully parsed */
  if (!reason_str) {
    ERROR(PLUGIN_NAME ": Invalid reason (%d) for domain state: %s", reason,
          state_str);
    return;
  }
#else
  const char *reason_str = "N/A";
#endif

  snprintf(msg, sizeof(msg), "Domain state: %s. Reason: %s", state_str,
           reason_str);

  int severity;
  switch (state) {
  case VIR_DOMAIN_NOSTATE:
  case VIR_DOMAIN_RUNNING:
  case VIR_DOMAIN_SHUTDOWN:
  case VIR_DOMAIN_SHUTOFF:
    severity = NOTIF_OKAY;
    break;
  case VIR_DOMAIN_BLOCKED:
  case VIR_DOMAIN_PAUSED:
#ifdef DOM_STATE_PMSUSPENDED
  case VIR_DOMAIN_PMSUSPENDED:
#endif
    severity = NOTIF_WARNING;
    break;
  case VIR_DOMAIN_CRASHED:
    severity = NOTIF_FAILURE;
    break;
  default:
    ERROR(PLUGIN_NAME ": Unrecognized domain state (%d)", state);
    return;
  }
  submit_notif(dom, severity, msg, "domain_state", NULL);
}