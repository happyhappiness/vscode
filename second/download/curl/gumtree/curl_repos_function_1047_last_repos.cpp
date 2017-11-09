static size_t display_gss_error(OM_uint32 status, int type,
                                char *buf, size_t len) {
  OM_uint32 maj_stat;
  OM_uint32 min_stat;
  OM_uint32 msg_ctx = 0;
  gss_buffer_desc status_string;

  do {
    maj_stat = gss_display_status(&min_stat,
                                  status,
                                  type,
                                  GSS_C_NO_OID,
                                  &msg_ctx,
                                  &status_string);
    if(GSS_LOG_BUFFER_LEN > len + status_string.length + 3) {
      len += snprintf(buf + len, GSS_LOG_BUFFER_LEN - len,
                      "%.*s. ", (int)status_string.length,
                      (char *)status_string.value);
    }
    gss_release_buffer(&min_stat, &status_string);
  } while(!GSS_ERROR(maj_stat) && msg_ctx != 0);

  return len;
}