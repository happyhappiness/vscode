static int sensor_convert_threshold_severity(enum ipmi_thresh_e severity) {
  switch (severity) {
  case IPMI_LOWER_NON_CRITICAL:
  case IPMI_UPPER_NON_CRITICAL:
    return NOTIF_OKAY;
  case IPMI_LOWER_CRITICAL:
  case IPMI_UPPER_CRITICAL:
    return NOTIF_WARNING;
  case IPMI_LOWER_NON_RECOVERABLE:
  case IPMI_UPPER_NON_RECOVERABLE:
    return NOTIF_FAILURE;
  default:
    return NOTIF_OKAY;
  } /* switch (severity) */
}