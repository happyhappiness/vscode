static int compact_ds_name(char *buffer, size_t buffer_size, char const *src) {
  char *src_copy;
  size_t src_len;
  char *ptr = buffer;
  size_t ptr_size = buffer_size;
  _Bool append_plus = 0;
  _Bool append_minus = 0;

  if ((buffer == NULL) || (buffer_size <= strlen("Minus")) || (src == NULL))
    return EINVAL;

  src_copy = strdup(src);
  src_len = strlen(src);

  /* Remove trailing "+" and "-". */
  if (src_copy[src_len - 1] == '+') {
    append_plus = 1;
    src_len--;
    src_copy[src_len] = 0;
  } else if (src_copy[src_len - 1] == '-') {
    append_minus = 1;
    src_len--;
    src_copy[src_len] = 0;
  }

  /* Split at special chars, capitalize first character, append to buffer. */
  char *dummy = src_copy;
  char *token;
  char *save_ptr = NULL;
  while ((token = strtok_r(dummy, ":_-+", &save_ptr)) != NULL) {
    size_t len;

    dummy = NULL;

    token[0] = toupper((int)token[0]);

    assert(ptr_size > 1);

    len = strlen(token);
    if (len >= ptr_size)
      len = ptr_size - 1;

    assert(len > 0);
    assert(len < ptr_size);

    sstrncpy(ptr, token, len + 1);
    ptr += len;
    ptr_size -= len;

    assert(*ptr == 0);
    if (ptr_size <= 1)
      break;
  }

  /* Append "Plus" or "Minus" if "+" or "-" has been stripped above. */
  if (append_plus || append_minus) {
    char const *append = "Plus";
    if (append_minus)
      append = "Minus";

    size_t offset = buffer_size - (strlen(append) + 1);
    if (offset > strlen(buffer))
      offset = strlen(buffer);

    sstrncpy(buffer + offset, append, buffer_size - offset);
  }

  sfree(src_copy);
  return 0;
}