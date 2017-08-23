{
  OM_uint32 maj_stat, min_stat;
  OM_uint32 msg_ctx = 0;
  gss_buffer_desc status_string;
  char buf[1024];
  size_t len;

  snprintf(buf, sizeof(buf), "%s", prefix);
  len = strlen(buf);
  do {
    maj_stat = gss_display_status(&min_stat,
                                  error_status,
                                  GSS_C_MECH_CODE,
                                  GSS_C_NO_OID,
                                  &msg_ctx,
                                  &status_string);
      if(sizeof(buf) > len + status_string.length + 1) {
        snprintf(buf + len, sizeof(buf) - len,
                 ": %s", (char*) status_string.value);
      len += status_string.length;
    }
    gss_release_buffer(&min_stat, &status_string);
  } while(!GSS_ERROR(maj_stat) && msg_ctx != 0);

  infof(conn->data, "%s\n", buf);
}