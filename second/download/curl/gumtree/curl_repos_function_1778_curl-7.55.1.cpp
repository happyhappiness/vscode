bool Curl_if_is_interface_name(const char *interf)
{
  /* This is here just to support the old interfaces */
  char buf[256];

  return (Curl_if2ip(AF_INET, 0 /* unused */, 0, interf, buf, sizeof(buf)) ==
          IF2IP_NOT_FOUND) ? FALSE : TRUE;
}