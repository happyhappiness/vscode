void Glob::Escape(int ch, char* buffer)
{
  if (! (
      'a' <= ch && ch <= 'z' ||
      'A' <= ch && ch <= 'Z' ||
      '0' <= ch && ch <= '9') )
    {
    sprintf(buffer, "\\%c", ch);
    }
  else
    {
#if defined( KWSYS_GLOB_CASE_INDEPENDENT )
    // On Windows and apple, no difference between lower and upper case
    sprintf(buffer, "%c", tolower(ch));
#else
    sprintf(buffer, "%c", ch);
#endif
    }
}