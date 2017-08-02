{
  int retcode;
  va_list ap_save; /* argument pointer */
  va_start(ap_save, format);
  retcode = curl_mvsnprintf(buffer, maxlength, format, ap_save);
  va_end(ap_save);
  return retcode;
}