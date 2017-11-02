static void time2str(char *r, curl_off_t seconds)
{
  curl_off_t d, h, m, s;
  if(seconds <= 0) {
    strcpy(r, "--:--:--");
    return;
  }
  h = seconds / CURL_OFF_T_C(3600);
  if(h <= CURL_OFF_T_C(99)) {
    m = (seconds - (h*CURL_OFF_T_C(3600))) / CURL_OFF_T_C(60);
    s = (seconds - (h*CURL_OFF_T_C(3600))) - (m*CURL_OFF_T_C(60));
    snprintf(r, 9, "%2" CURL_FORMAT_CURL_OFF_T ":%02" CURL_FORMAT_CURL_OFF_T
             ":%02" CURL_FORMAT_CURL_OFF_T, h, m, s);
  }
  else {
    /* this equals to more than 99 hours, switch to a more suitable output
       format to fit within the limits. */
    d = seconds / CURL_OFF_T_C(86400);
    h = (seconds - (d*CURL_OFF_T_C(86400))) / CURL_OFF_T_C(3600);
    if(d <= CURL_OFF_T_C(999))
      snprintf(r, 9, "%3" CURL_FORMAT_CURL_OFF_T
               "d %02" CURL_FORMAT_CURL_OFF_T "h", d, h);
    else
      snprintf(r, 9, "%7" CURL_FORMAT_CURL_OFF_T "d", d);
  }
}