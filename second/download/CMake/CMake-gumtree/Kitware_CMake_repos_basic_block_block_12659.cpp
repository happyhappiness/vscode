{
      memcpy(&rar->unp_buffer[rar->unp_offset],
             &rar->lzss.window[windowoffs], length);
    }