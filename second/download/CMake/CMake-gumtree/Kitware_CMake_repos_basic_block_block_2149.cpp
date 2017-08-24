(memcmp(static_cast<const void*>(source_buf),
               static_cast<const void*>(dest_buf),
               static_cast<size_t>(nnext)) != 0) {
      return true;
    }