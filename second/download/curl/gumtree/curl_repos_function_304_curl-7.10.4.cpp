static struct hostent* pack_hostent(char** buf, struct hostent* orig)
{
  char *bufptr;
  char *newbuf;
  struct hostent* copy;

  int i;
  char *str;
  int len;

  bufptr = *buf;
  copy = (struct hostent*)bufptr;

  bufptr += sizeof(struct hostent);
  copy->h_name = bufptr;
  len = strlen(orig->h_name) + 1;
  strncpy(bufptr, orig->h_name, len);
  bufptr += len;

  /* we align on even 64bit boundaries for safety */
#define MEMALIGN(x) ((x)+(8-(((unsigned long)(x))&0x7)))

  /* This must be aligned properly to work on many CPU architectures! */
  bufptr = MEMALIGN(bufptr);
  
  copy->h_aliases = (char**)bufptr;

  /* Figure out how many aliases there are */
  for (i = 0; orig->h_aliases[i] != NULL; ++i);

  /* Reserve room for the array */
  bufptr += (i + 1) * sizeof(char*);

  /* Clone all known aliases */
  for(i = 0; (str = orig->h_aliases[i]); i++) {
    len = strlen(str) + 1;
    strncpy(bufptr, str, len);
    copy->h_aliases[i] = bufptr;
    bufptr += len;
  }
  /* Terminate the alias list with a NULL */
  copy->h_aliases[i] = NULL;

  copy->h_addrtype = orig->h_addrtype;
  copy->h_length = orig->h_length;
    
  /* align it for (at least) 32bit accesses */
  bufptr = MEMALIGN(bufptr);

  copy->h_addr_list = (char**)bufptr;

  /* Figure out how many addresses there are */
  for (i = 0; orig->h_addr_list[i] != NULL; ++i);

  /* Reserve room for the array */
  bufptr += (i + 1) * sizeof(char*);

  i = 0;
  len = orig->h_length;
  str = orig->h_addr_list[i];
  while (str != NULL) {
    memcpy(bufptr, str, len);
    copy->h_addr_list[i] = bufptr;
    bufptr += len;
    str = orig->h_addr_list[++i];
  }
  copy->h_addr_list[i] = NULL;

  /* now, shrink the allocated buffer to the size we actually need, which
     most often is only a fraction of the original alloc */
  newbuf=(char *)realloc(*buf, (int)bufptr-(int)(*buf));

  /* if the alloc moved, we need to adjust things again */
  if(newbuf != *buf)
    hostcache_fixoffset((struct hostent*)newbuf, (int)newbuf-(int)*buf);

  /* setup the return */
  *buf = newbuf;
  copy = (struct hostent*)newbuf;

  return copy;
}