static void get_sdp_filename(const char *url, char *sdp_filename)
{
  const char *s = strrchr(url, '/');
  strcpy(sdp_filename, "video.sdp");
  if (s != NULL) {
    s++;
    if (s[0] != '\0') {
      sprintf(sdp_filename, "%s.sdp", s);
    }
  }
}