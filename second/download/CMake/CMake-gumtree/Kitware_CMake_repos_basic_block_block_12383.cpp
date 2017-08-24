(dstoffs > srcoffs) {
      if (l > lzss_size(&rar->lzss) - dstoffs)
        l = lzss_size(&rar->lzss) - dstoffs;
    } else {
      if (l > lzss_size(&rar->lzss) - srcoffs)
        l = lzss_size(&rar->lzss) - srcoffs;
    }