{
      /*
       * Set the returned offset but only seek to the end of
       * the data block.
       */
      rar->offset_seek = client_offset;
      client_offset = rar->unp_size;
    }