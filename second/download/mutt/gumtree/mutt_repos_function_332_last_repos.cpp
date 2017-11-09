static inline char *skip_email_wsp(const char *s)
{
  if (s)
    return (char *)(s + strspn(s, EMAIL_WSP));
  return (char *)s;
}