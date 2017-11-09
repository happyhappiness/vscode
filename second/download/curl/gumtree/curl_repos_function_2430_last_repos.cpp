static bool is_separator(char c)
{
  /* Return whether character is a cipher list separator. */
  switch(c) {
  case ' ':
  case '\t':
  case ':':
  case ',':
  case ';':
    return true;
  }
  return false;
}