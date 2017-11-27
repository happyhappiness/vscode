char *subst(char *buf, size_t buflen, const char *string, size_t off1,
            size_t off2, const char *replacement) {
  char *out = buf;

  char const *front;
  char const *back;
  size_t front_len;
  size_t replacement_len;
  size_t back_len;

  if ((NULL == buf) || (0 == buflen) || (NULL == string) ||
      (NULL == replacement))
    return NULL;

  size_t string_len = strlen(string);
  if ((off1 > string_len) || (off2 > string_len) || (off1 > off2))
    return NULL;

  front = string;
  back = string + off2;
  front_len = off1;
  replacement_len = strlen(replacement);
  back_len = strlen(back);

  if (front_len >= buflen) {
    front_len = buflen - 1;
    replacement_len = 0;
    back_len = 0;
  } else if ((front_len + replacement_len) >= buflen) {
    replacement_len = buflen - (front_len + 1);
    back_len = 0;
  } else if ((front_len + replacement_len + back_len) >= buflen) {
    back_len = buflen - (front_len + replacement_len + 1);
  } else {
    buflen = front_len + replacement_len + back_len + 1;
  }
  assert((front_len + replacement_len + back_len) == (buflen - 1));

  if (front_len != 0) {
    sstrncpy(out, front, front_len + 1);
    out += front_len;
  }

  if (replacement_len != 0) {
    sstrncpy(out, replacement, replacement_len + 1);
    out += replacement_len;
  }

  if (back_len != 0) {
    sstrncpy(out, back, back_len + 1);
    out += back_len;
  }

  out[0] = 0;
  return buf;
}