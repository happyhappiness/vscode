f(info.max == info.length)
      /* we're at maximum, scrap the last letter */
      info.buffer[-1] = 0;
    else
      info.buffer[0] = 0