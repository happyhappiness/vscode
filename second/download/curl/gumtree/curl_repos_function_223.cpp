static int get_char(char c, int base)
{
  int value = -1;
  if (c <= '9' && c >= '0') {
    value = c - '0';
  }
  else if (c <= 'Z' && c >= 'A') {
    value = c - 'A' + 10;
  }
  else if (c <= 'z' && c >= 'a') {
    value = c - 'a' + 10;
  }

  if (value >= base) {
    value = -1;
  }

  return value;
}