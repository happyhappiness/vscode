{
  nghttp2_info *h2 = nghttp2_version(0);
  return snprintf(p, len, " nghttp2/%s", h2->version_str);
}