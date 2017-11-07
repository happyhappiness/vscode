wchar_t replacement_char ()
{
  return Charset_is_utf8 ? 0xfffd : '?';
}