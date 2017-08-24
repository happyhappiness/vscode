{
        if (memcmp(p, RAR_SIGNATURE, 7) == 0)
          return (30);
        p += 0x10;
      }