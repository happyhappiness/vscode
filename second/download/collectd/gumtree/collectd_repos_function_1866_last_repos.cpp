static void cut_suffix(char *buffer, size_t buffer_size, char const *str,
                       char const *suffix) {

  size_t str_len = strlen(str);
  size_t suffix_len = strlen(suffix);

  size_t offset = str_len - suffix_len + 1;

  if (offset > buffer_size) {
    offset = buffer_size;
  }

  sstrncpy(buffer, str, offset);
}