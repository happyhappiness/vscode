void Curl_gss_log_error(struct Curl_easy *data, const char *prefix,
                        OM_uint32 major, OM_uint32 minor)
{
  char buf[GSS_LOG_BUFFER_LEN];
  size_t len = 0;

  if(major != GSS_S_FAILURE)
    len = display_gss_error(major, GSS_C_GSS_CODE, buf, len);

  display_gss_error(minor, GSS_C_MECH_CODE, buf, len);

  infof(data, "%s%s\n", prefix, buf);
}