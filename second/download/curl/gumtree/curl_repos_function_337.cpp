static int
convert_version_info_string(const char * * stringp,
                            char * * bufp, int * left, unsigned int ccsid)

{
  /* Helper for curl_version_info_ccsid(): convert a string if defined.
     Result is stored in the `*left'-byte buffer at `*bufp'.
     `*bufp' and `*left' are updated accordingly.
     Return 0 if ok, else -1. */

  if(*stringp) {
    int l = convert(*bufp, *left, ccsid, *stringp, -1, ASCII_CCSID);

    if(l <= 0)
      return -1;

    *stringp = *bufp;
    *bufp += l;
    *left -= l;
    }

  return 0;
}