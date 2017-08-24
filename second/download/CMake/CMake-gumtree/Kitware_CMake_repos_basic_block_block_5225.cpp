{
      /* ignore return code, use default value if it fails */
      (void)sscanf(pbsz, "PBSZ=%u", &buffer_size);
      if(buffer_size < conn->buffer_size)
        conn->buffer_size = buffer_size;
    }