             &rar->lzss.window[windowoffs], firstpart);
      memcpy(&rar->unp_buffer[rar->unp_offset + firstpart],
             &rar->lzss.window[0], length - firstpart);
    } else
      memcpy(&rar->unp_buffer[rar->unp_offset],
             &rar->lzss.window[windowoffs], length);
  }
  rar->unp_offset += length;
  if (rar->unp_offset >= rar->unp_buffer_size)