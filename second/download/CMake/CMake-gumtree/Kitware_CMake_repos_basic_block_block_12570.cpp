(i = 0; i < MAX_SYMBOLS;)
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