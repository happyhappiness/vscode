wchar_t replacement_char (void)
{
  return Charset_is_utf8 ? 0xfffd : '?';
}