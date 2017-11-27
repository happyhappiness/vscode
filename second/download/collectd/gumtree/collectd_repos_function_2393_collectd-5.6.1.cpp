int format_name (char *ret, int ret_len,
		const char *hostname,
		const char *plugin, const char *plugin_instance,
		const char *type, const char *type_instance)
{
  char *buffer;
  size_t buffer_size;

  buffer = ret;
  buffer_size = (size_t) ret_len;

#define APPEND(str) do {                                               \
  size_t l = strlen (str);                                             \
  if (l >= buffer_size)                                                \
    return (ENOBUFS);                                                  \
  memcpy (buffer, (str), l);                                           \
  buffer += l; buffer_size -= l;                                       \
} while (0)

  assert (plugin != NULL);
  assert (type != NULL);

  APPEND (hostname);
  APPEND ("/");
  APPEND (plugin);
  if ((plugin_instance != NULL) && (plugin_instance[0] != 0))
  {
    APPEND ("-");
    APPEND (plugin_instance);
  }
  APPEND ("/");
  APPEND (type);
  if ((type_instance != NULL) && (type_instance[0] != 0))
  {
    APPEND ("-");
    APPEND (type_instance);
  }
  assert (buffer_size > 0);
  buffer[0] = 0;

#undef APPEND
  return (0);
}