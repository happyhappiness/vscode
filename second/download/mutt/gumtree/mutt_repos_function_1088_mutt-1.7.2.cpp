static void
extract_number (dest, source)
    int *dest;
    unsigned char *source;
{
  int temp = SIGN_EXTEND_CHAR (*(source + 1));
  *dest = *source & 0377;
  *dest += temp << 8;
}