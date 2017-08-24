{
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