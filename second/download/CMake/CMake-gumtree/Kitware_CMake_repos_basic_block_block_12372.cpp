(br->avail_in <= 0) {

      if (rar->bytes_unconsumed > 0) {
        /* Consume as much as the decompressor
         * actually used. */
        __archive_read_consume(a, rar->bytes_unconsumed);
        rar->bytes_unconsumed = 0;
      }
      br->next_in = rar_read_ahead(a, 1, &(br->avail_in));
      if (br->next_in == NULL)
        return (0);
      if (br->avail_in == 0)
        return (0);
    }