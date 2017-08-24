f(!strncmp("./", clone, 2)) {
      clone+=2;
      clen-=2;
    }
    else if(!strncmp("../", clone, 3)) {
      clone+=3;
      clen-=3;
    }

    /*  B.  if the input buffer begins with a prefix of "/./" or "/.", where
        "."  is a complete path segment, then replace that prefix with "/" in
        the input buffer; otherwise, */
    else if(!strncmp("/./", clone, 3)) {
      clone+=2;
      clen-=2;
    }
    else if(!strcmp("/.", clone)) {
      clone[1]='/';
      clone++;
      clen-=1;
    }

    /*  C.  if the input buffer begins with a prefix of "/../" or "/..", where
        ".." is a complete path segment, then replace that prefix with "/" in
        the input buffer and remove the last segment and its preceding "/" (if
        any) from the output buffer; otherwise, */

    else if(!strncmp("/../", clone, 4)) {
      clone+=3;
      clen-=3;
      /* remove the last segment from the output buffer */
      while(outptr > out) {
        outptr--;
        if(*outptr == '/')
          break;
      }
      *outptr = 0; /* zero-terminate where it stops */
    }
    else if(!strcmp("/..", clone)) {
      clone[2]='/';
      clone+=2;
      clen-=2;
      /* remove the last segment from the output buffer */
      while(outptr > out) {
        outptr--;
        if(*outptr == '/')
          break;
      }
      *outptr = 0; /* zero-terminate where it stops */
    }

    /*  D.  if the input buffer consists only of "." or "..", then remove
        that from the input buffer; otherwise, */

    else if(!strcmp(".", clone) || !strcmp("..", clone)) {
      *clone=0;
      *out=0;
    }

    else {
      /*  E.  move the first path segment in the input buffer to the end of
          the output buffer, including the initial "/" character (if any) and
          any subsequent characters up to, but not including, the next "/"
          character or the end of the input buffer. */

      do {
        *outptr++ = *clone++;
        clen--;
      } while(*clone && (*clone != '/'));
      *outptr = 0;
    }