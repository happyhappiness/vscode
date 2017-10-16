    else
      if ( buffer[i] == '\b')
        /* remove this letter and if this is not the first key, remove the
           previous one as well */
        i = i - (i>=1?2:1);
  }
  /* since echo is disabled, print a newline */
  fputs("\n", stderr);
  /* if user didn't hit ENTER, terminate buffer */
  if (i==buflen)
    buffer[buflen-1]=0;

  return buffer; /* we always return success */
}
