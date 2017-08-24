(symbol <= 262)
    {
      offsindex = symbol - 259;
      offs = rar->oldoffset[offsindex];

      if ((lensymbol = read_next_symbol(a, &rar->lengthcode)) < 0)
        goto bad_data;
      if (lensymbol > (int)(sizeof(lengthbases)/sizeof(lengthbases[0])))
        goto bad_data;
      if (lensymbol > (int)(sizeof(lengthbits)/sizeof(lengthbits[0])))
        goto bad_data;
      len = lengthbases[lensymbol] + 2;
      if (lengthbits[lensymbol] > 0) {
        if (!rar_br_read_ahead(a, br, lengthbits[lensymbol]))
          goto truncated_data;
        len += rar_br_bits(br, lengthbits[lensymbol]);
        rar_br_consume(br, lengthbits[lensymbol]);
      }

      for (i = offsindex; i > 0; i--)
        rar->oldoffset[i] = rar->oldoffset[i-1];
      rar->oldoffset[0] = offs;
    }