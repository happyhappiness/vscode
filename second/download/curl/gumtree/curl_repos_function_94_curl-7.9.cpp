static BOOL dprintf_IsQualifierNoDollar(char c)
{
  switch (c) {
  case '-': case '+': case ' ': case '#': case '.':
  case '0': case '1': case '2': case '3': case '4':
  case '5': case '6': case '7': case '8': case '9':
  case 'h': case 'l': case 'L': case 'Z': case 'q':
    return TRUE;
  default:
    return FALSE;
  }
}