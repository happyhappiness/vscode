(rar->unp_offset >= rar->unp_buffer_size)
    *buffer = rar->unp_buffer;
  else
    *buffer = NULL