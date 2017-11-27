static void lcc_chomp(char *str) /* {{{ */
{
  size_t str_len;

  str_len = strlen(str);
  while (str_len > 0) {
    if (str[str_len - 1] >= 32)
      break;
    str[str_len - 1] = 0;
    str_len--;
  }
}