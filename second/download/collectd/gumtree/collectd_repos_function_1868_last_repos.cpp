static int parse_keys(char *buffer, size_t buffer_size, const char *key_str) {
  char tmp[2 * buffer_size];
  size_t tmp_size = sizeof(tmp);
  const char *cut_suffixes[] = {".type", ".avgcount", ".sum", ".avgtime"};

  if (buffer == NULL || buffer_size == 0 || key_str == NULL ||
      strlen(key_str) == 0)
    return EINVAL;

  sstrncpy(tmp, key_str, tmp_size);

  /* Strip suffix if it is ".type" or one of latency metric suffix. */
  if (count_parts(key_str) > 2) {
    for (size_t i = 0; i < STATIC_ARRAY_SIZE(cut_suffixes); i++) {
      if (has_suffix(key_str, cut_suffixes[i])) {
        cut_suffix(tmp, tmp_size, key_str, cut_suffixes[i]);
        break;
      }
    }
  }

  return compact_ds_name(buffer, buffer_size, tmp);
}