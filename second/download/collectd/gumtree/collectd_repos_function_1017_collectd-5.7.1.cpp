static char *get_module_name(char *buf, size_t buf_len, const char *module) {
  int status = 0;
  if (base_name[0] == '\0')
    status = ssnprintf(buf, buf_len, "%s", module);
  else
    status = ssnprintf(buf, buf_len, "%s::%s", base_name, module);
  if ((status < 0) || ((unsigned int)status >= buf_len))
    return (NULL);
  return (buf);
}