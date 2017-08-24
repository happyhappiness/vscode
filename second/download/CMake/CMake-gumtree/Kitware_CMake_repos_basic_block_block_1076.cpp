{
      /*
       * On big-endian machines, we must arrange the bytes in the
       * right order.
       */
      const md5_byte_t* xp = data;
      int i;

#if BYTE_ORDER == 0
      X = xbuf; /* (dynamic only) */
#else
#define xbuf X /* (static only) */
#endif
      for (i = 0; i < 16; ++i, xp += 4)
        xbuf[i] =
          (md5_word_t)(xp[0] + (xp[1] << 8) + (xp[2] << 16) + (xp[3] << 24));
    }