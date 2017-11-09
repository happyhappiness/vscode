static inline int is_shell_char(wchar_t ch)
{
  static const wchar_t shell_chars[] = L"<>&()$?*;{}| "; /* ! not included because it can be part of a pathname in Mutt */
  return wcschr(shell_chars, ch) != NULL;
}