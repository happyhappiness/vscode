{
    rar_br_consume(br, 1);

    /* Keep existing table flag */
    if (!rar_br_read_ahead(a, br, 1))
      goto truncated_data;
    if (!rar_br_bits(br, 1))
      memset(rar->lengthtable, 0, sizeof(rar->lengthtable));
    rar_br_consume(br, 1);

    memset(&bitlengths, 0, sizeof(bitlengths));
    for (i = 0; i < MAX_SYMBOLS;)
    {
      if (!rar_br_read_ahead(a, br, 4))
        goto truncated_data;
      bitlengths[i++] = rar_br_bits(br, 4);
      rar_br_consume(br, 4);
      if (bitlengths[i-1] == 0xF)
      {
        if (!rar_br_read_ahead(a, br, 4))
          goto truncated_data;
        zerocount = rar_br_bits(br, 4);
        rar_br_consume(br, 4);
        if (zerocount)
        {
          i--;
          for (j = 0; j < zerocount + 2 && i < MAX_SYMBOLS; j++)
            bitlengths[i++] = 0;
        }
      }
    }

    memset(&precode, 0, sizeof(precode));
    r = create_code(a, &precode, bitlengths, MAX_SYMBOLS, MAX_SYMBOL_LENGTH);
    if (r != ARCHIVE_OK) {
      free(precode.tree);
      free(precode.table);
      return (r);
    }

    for (i = 0; i < HUFFMAN_TABLE_SIZE;)
    {
      if ((val = read_next_symbol(a, &precode)) < 0) {
        free(precode.tree);
        free(precode.table);
        return (ARCHIVE_FATAL);
      }
      if (val < 16)
      {
        rar->lengthtable[i] = (rar->lengthtable[i] + val) & 0xF;
        i++;
      }
      else if (val < 18)
      {
        if (i == 0)
        {
          free(precode.tree);
          free(precode.table);
          archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                            "Internal error extracting RAR file.");
          return (ARCHIVE_FATAL);
        }

        if(val == 16) {
          if (!rar_br_read_ahead(a, br, 3)) {
            free(precode.tree);
            free(precode.table);
            goto truncated_data;
          }
          n = rar_br_bits(br, 3) + 3;
          rar_br_consume(br, 3);
        } else {
          if (!rar_br_read_ahead(a, br, 7)) {
            free(precode.tree);
            free(precode.table);
            goto truncated_data;
          }
          n = rar_br_bits(br, 7) + 11;
          rar_br_consume(br, 7);
        }

        for (j = 0; j < n && i < HUFFMAN_TABLE_SIZE; j++)
        {
          rar->lengthtable[i] = rar->lengthtable[i-1];
          i++;
        }
      }
      else
      {
        if(val == 18) {
          if (!rar_br_read_ahead(a, br, 3)) {
            free(precode.tree);
            free(precode.table);
            goto truncated_data;
          }
          n = rar_br_bits(br, 3) + 3;
          rar_br_consume(br, 3);
        } else {
          if (!rar_br_read_ahead(a, br, 7)) {
            free(precode.tree);
            free(precode.table);
            goto truncated_data;
          }
          n = rar_br_bits(br, 7) + 11;
          rar_br_consume(br, 7);
        }

        for(j = 0; j < n && i < HUFFMAN_TABLE_SIZE; j++)
          rar->lengthtable[i++] = 0;
      }
    }
    free(precode.tree);
    free(precode.table);

    r = create_code(a, &rar->maincode, &rar->lengthtable[0], MAINCODE_SIZE,
                MAX_SYMBOL_LENGTH);
    if (r != ARCHIVE_OK)
      return (r);
    r = create_code(a, &rar->offsetcode, &rar->lengthtable[MAINCODE_SIZE],
                OFFSETCODE_SIZE, MAX_SYMBOL_LENGTH);
    if (r != ARCHIVE_OK)
      return (r);
    r = create_code(a, &rar->lowoffsetcode,
                &rar->lengthtable[MAINCODE_SIZE + OFFSETCODE_SIZE],
                LOWOFFSETCODE_SIZE, MAX_SYMBOL_LENGTH);
    if (r != ARCHIVE_OK)
      return (r);
    r = create_code(a, &rar->lengthcode,
                &rar->lengthtable[MAINCODE_SIZE + OFFSETCODE_SIZE +
                LOWOFFSETCODE_SIZE], LENGTHCODE_SIZE, MAX_SYMBOL_LENGTH);
    if (r != ARCHIVE_OK)
      return (r);
  }