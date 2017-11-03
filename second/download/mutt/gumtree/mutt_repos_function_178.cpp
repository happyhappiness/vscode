int mutt_rx_sanitize_string (char *dest, size_t destlen, const char *src)
{
  while (*src && --destlen > 2)
  {
    if (strchr (rx_special_chars, *src))
    {
      *dest++ = '\\';
      destlen--;
    }
    *dest++ = *src++;
  }
  
  *dest = '\0';
  
  if (*src)
    return -1;
  else
    return 0;
}