static
char *appendstring(char *string, /* original string */
                   char *buffer, /* to append */
                   int *stringlen, int *stralloc)
{
  int len = strlen(buffer);

  if((len + *stringlen) > *stralloc) {
    char *newptr= realloc(string, *stralloc*2);
    if(newptr) {
      string = newptr;
      *stralloc *= 2;
    }
    else
      return NULL;
  }
  strcpy(&string[*stringlen], buffer);
  *stringlen += len;

  return string;
}