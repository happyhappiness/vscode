static inline void
set_uint32 (char *cp, md5_uint32 v)
{
  memcpy (cp, &v, sizeof v);
}