{
        if (!memcmp(strp, "\x00\\", 2))
          *(strp + 1) = '/';
        strp += 2;
      }