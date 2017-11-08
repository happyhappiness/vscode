char *match_url(char *filename, URLGlob *glob)
{
  char *target;
  URLPattern pat;
  int i;
  int allocsize;
  int stringlen=0;
  char numbuf[18];
  char *appendthis;
  int appendlen;

  /* We cannot use the glob_buffer for storage here since the filename may
   * be longer than the URL we use. We allocate a good start size, then
   * we need to realloc in case of need.
   */
  allocsize=strlen(filename);
  target = malloc(allocsize);
  if(NULL == target)
    return NULL; /* major failure */

  while (*filename != '\0') {
    if (*filename == '#') {
      if (!isdigit((int)*++filename) ||
	  *filename == '0') {		/* only '#1' ... '#9' allowed */
	/* printf("illegal matching expression\n");
           exit(CURLE_URL_MALFORMAT);*/
        continue;
      }
      i = *filename - '1';
      if (i + 1 > glob->size / 2) {
	/*printf("match against nonexisting pattern\n");
          exit(CURLE_URL_MALFORMAT);*/
        continue;
      }
      pat = glob->pattern[i];
      switch (pat.type) {
      case UPTSet:
	appendthis = pat.content.Set.elements[pat.content.Set.ptr_s];
	appendlen = (int)strlen(pat.content.Set.elements[pat.content.Set.ptr_s]);
	break;
      case UPTCharRange:
        numbuf[0]=pat.content.CharRange.ptr_c;
        numbuf[1]=0;
        appendthis=numbuf;
        appendlen=1;
	break;
      case UPTNumRange:
	sprintf(numbuf, "%0*d", pat.content.NumRange.padlength, pat.content.NumRange.ptr_n);
        appendthis = numbuf;
        appendlen = (int)strlen(numbuf);
	break;
      default:
	printf("internal error: invalid pattern type (%d)\n", pat.type);
        return NULL;
      }
      ++filename;
    }
    else {
      appendthis=filename++;
      appendlen=1;
    }
    if(appendlen + stringlen >= allocsize) {
      char *newstr;
      allocsize = (appendlen + stringlen)*2;
      newstr=realloc(target, allocsize);
      if(NULL ==newstr) {
        free(target);
        return NULL;
      }
      target=newstr;
    }
    memcpy(&target[stringlen], appendthis, appendlen);
    stringlen += appendlen;
  }
  target[stringlen]= '\0';
  return target;
}