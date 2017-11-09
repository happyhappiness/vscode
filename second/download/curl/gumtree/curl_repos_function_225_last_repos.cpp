static int older_progress(void *p,
                          double dltotal, double dlnow,
                          double ultotal, double ulnow)
{
  return xferinfo(p,
                  (curl_off_t)dltotal,
                  (curl_off_t)dlnow,
                  (curl_off_t)ultotal,
                  (curl_off_t)ulnow);
}