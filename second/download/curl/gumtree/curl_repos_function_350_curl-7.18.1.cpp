static int my_seek(void *stream, curl_off_t offset, int whence)
{
  struct InStruct *in=(struct InStruct *)stream;

#if (SIZEOF_CURL_OFF_T > SIZEOF_OFF_T) && !defined(lseek)
  /* The sizeof check following here is only interesting if curl_off_t is
     larger than off_t, but also not on windows-like systems for which lseek
     is a defined macro that works around the 32bit off_t-problem and thus do
     64bit seeks correctly anyway */

  if(offset > MAX_SEEK) {
    /* Some precaution code to work around problems with different data sizes
       to allow seeking >32bit even if off_t is 32bit. Should be very rare and
       is really valid on weirdo-systems. */
    curl_off_t left = offset;

    if(whence != SEEK_SET)
      /* this code path doesn't support other types */
      return 1;

    if(-1 == lseek(in->fd, 0, SEEK_SET))
      /* couldn't rewind to beginning */
      return 1;

    while(left) {
      long step = (left>MAX_SEEK ? MAX_SEEK : (long)left);
      if(-1 == lseek(in->fd, step, SEEK_CUR))
        /* couldn't seek forwards the desired amount */
        return 1;
      left -= step;
    }
    return 0;
  }
#endif
  if(-1 == lseek(in->fd, offset, whence))
    /* couldn't rewind, the reason is in errno but errno is just not
       portable enough and we don't actually care that much why we failed. */
    return 1;

  return 0;
}