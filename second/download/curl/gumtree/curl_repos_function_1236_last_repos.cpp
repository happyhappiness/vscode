static CURLcode
get_pathname(const char **cpp, char **path)
{
  const char *cp = *cpp, *end;
  char quot;
  unsigned int i, j;
  static const char WHITESPACE[] = " \t\r\n";

  cp += strspn(cp, WHITESPACE);
  if(!*cp) {
    *cpp = cp;
    *path = NULL;
    return CURLE_QUOTE_ERROR;
  }

  *path = malloc(strlen(cp) + 1);
  if(*path == NULL)
    return CURLE_OUT_OF_MEMORY;

  /* Check for quoted filenames */
  if(*cp == '\"' || *cp == '\'') {
    quot = *cp++;

    /* Search for terminating quote, unescape some chars */
    for(i = j = 0; i <= strlen(cp); i++) {
      if(cp[i] == quot) {  /* Found quote */
        i++;
        (*path)[j] = '\0';
        break;
      }
      if(cp[i] == '\0') {  /* End of string */
        /*error("Unterminated quote");*/
        goto fail;
      }
      if(cp[i] == '\\') {  /* Escaped characters */
        i++;
        if(cp[i] != '\'' && cp[i] != '\"' &&
            cp[i] != '\\') {
          /*error("Bad escaped character '\\%c'",
              cp[i]);*/
          goto fail;
        }
      }
      (*path)[j++] = cp[i];
    }

    if(j == 0) {
      /*error("Empty quotes");*/
      goto fail;
    }
    *cpp = cp + i + strspn(cp + i, WHITESPACE);
  }
  else {
    /* Read to end of filename */
    end = strpbrk(cp, WHITESPACE);
    if(end == NULL)
      end = strchr(cp, '\0');
    *cpp = end + strspn(end, WHITESPACE);

    memcpy(*path, cp, end - cp);
    (*path)[end - cp] = '\0';
  }
  return CURLE_OK;

  fail:
  Curl_safefree(*path);
  return CURLE_QUOTE_ERROR;
}