static void strcpy_url(char *output, char *url)
{
  /* we must add this with whitespace-replacing */
  bool left=TRUE;
  char *iptr;
  char *optr = output;
  for(iptr = url;    /* read from here */
      *iptr;         /* until zero byte */
      iptr++) {
    switch(*iptr) {
    case '?':
      left=FALSE;
    default:
      *optr++=*iptr;
      break;
    case ' ':
      if(left) {
        *optr++='%'; /* add a '%' */
        *optr++='2'; /* add a '2' */
        *optr++='0'; /* add a '0' */
      }
      else
        *optr++='+'; /* add a '+' here */
      break;
    }
  }
  *optr=0; /* zero terminate output buffer */

}