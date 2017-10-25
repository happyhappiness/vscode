char *match_url(char *filename, URLGlob glob) {
  char *buf = glob_buffer;
  URLPattern pat;
  int i;

  while (*filename != '\0') {
    if (*filename == '#') {
      if (!isdigit((int)*++filename) ||
	  *filename == '0') {		/* only '#1' ... '#9' allowed */
	printf("illegal matching expression\n");
	exit(CURLE_URL_MALFORMAT);
      }
      i = *filename - '1';
      if (i + 1 > glob.size / 2) {
	printf("match against nonexisting pattern\n");
	exit(CURLE_URL_MALFORMAT);
      }
      pat = glob.pattern[i];
      switch (pat.type) {
      case UPTSet:
	strcpy(buf, pat.content.Set.elements[pat.content.Set.ptr_s]);
	buf += strlen(pat.content.Set.elements[pat.content.Set.ptr_s]);
	break;
      case UPTCharRange:
	*buf++ = pat.content.CharRange.ptr_c;
	break;
      case UPTNumRange:
	sprintf(buf, "%0*d", pat.content.NumRange.padlength, pat.content.NumRange.ptr_n);
        buf += strlen(buf);
	break;
      default:
	printf("internal error: invalid pattern type (%d)\n", pat.type);
	exit (CURLE_FAILED_INIT);
      }
      ++filename;
    }
    else
      *buf++ = *filename++;
  }
  *buf = '\0';
  return strdup(glob_buffer);
}