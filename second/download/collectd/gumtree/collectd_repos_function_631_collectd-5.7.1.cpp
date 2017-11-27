static char *replace_json_reserved(const char *message) /* {{{ */
{
  char *msg = replace_str(message, "\\", "\\\\");
  if (msg == NULL) {
    ERROR("write_sensu plugin: Unable to alloc memory");
    return NULL;
  }
  char *tmp = replace_str(msg, "\"", "\\\"");
  free(msg);
  if (tmp == NULL) {
    ERROR("write_sensu plugin: Unable to alloc memory");
    return NULL;
  }
  msg = replace_str(tmp, "\n", "\\\n");
  free(tmp);
  if (msg == NULL) {
    ERROR("write_sensu plugin: Unable to alloc memory");
    return NULL;
  }
  return msg;
}