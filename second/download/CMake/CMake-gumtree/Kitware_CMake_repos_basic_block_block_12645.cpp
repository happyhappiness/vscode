{
    if (rar->output_last_match &&
      lzss_position(&rar->lzss) + rar->lastlength <= end)
    {
      lzss_emit_match(rar, rar->lastoffset, rar->lastlength);
      rar->output_last_match = 0;
    }

    if(rar->is_ppmd_block || rar->output_last_match ||
      lzss_position(&rar->lzss) >= end)
      return lzss_position(&rar->lzss);

    if ((symbol = read_next_symbol(a, &rar->maincode)) < 0)
      return (ARCHIVE_FATAL);
    rar->output_last_match = 0;

    if (symbol < 256)
    {
      lzss_emit_literal(rar, symbol);
      continue;
    }
    else if (symbol == 256)
    {
      if (!rar_br_read_ahead(a, br, 1))
        goto truncated_data;
      newfile = !rar_br_bits(br, 1);
      rar_br_consume(br, 1);

      if(newfile)
      {
        rar->start_new_block = 1;
        if (!rar_br_read_ahead(a, br, 1))
          goto truncated_data;
        rar->start_new_table = rar_br_bits(br, 1);
        rar_br_consume(br, 1);
        return lzss_position(&rar->lzss);
      }
      else
      {
        if (parse_codes(a) != ARCHIVE_OK)
          return (ARCHIVE_FATAL);
        continue;
      }
    }
    else if(symbol==257)
    {
      archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
                        "Parsing filters is unsupported.");
      return (ARCHIVE_FAILED);
    }
    else if(symbol==258)
    {
      if(rar->lastlength == 0)
        continue;

      offs = rar->lastoffset;
      len = rar->lastlength;
    }
    else if (symbol <= 262)
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
    else if(symbol<=270)
    {
      offs = shortbases[symbol-263] + 1;
      if(shortbits[symbol-263] > 0) {
        if (!rar_br_read_ahead(a, br, shortbits[symbol-263]))
          goto truncated_data;
        offs += rar_br_bits(br, shortbits[symbol-263]);
        rar_br_consume(br, shortbits[symbol-263]);
      }

      len = 2;

      for(i = 3; i > 0; i--)
        rar->oldoffset[i] = rar->oldoffset[i-1];
      rar->oldoffset[0] = offs;
    }
    else
    {
      if (symbol-271 > (int)(sizeof(lengthbases)/sizeof(lengthbases[0])))
        goto bad_data;
      if (symbol-271 > (int)(sizeof(lengthbits)/sizeof(lengthbits[0])))
        goto bad_data;
      len = lengthbases[symbol-271]+3;
      if(lengthbits[symbol-271] > 0) {
        if (!rar_br_read_ahead(a, br, lengthbits[symbol-271]))
          goto truncated_data;
        len += rar_br_bits(br, lengthbits[symbol-271]);
        rar_br_consume(br, lengthbits[symbol-271]);
      }

      if ((offssymbol = read_next_symbol(a, &rar->offsetcode)) < 0)
        goto bad_data;
      if (offssymbol > (int)(sizeof(offsetbases)/sizeof(offsetbases[0])))
        goto bad_data;
      if (offssymbol > (int)(sizeof(offsetbits)/sizeof(offsetbits[0])))
        goto bad_data;
      offs = offsetbases[offssymbol]+1;
      if(offsetbits[offssymbol] > 0)
      {
        if(offssymbol > 9)
        {
          if(offsetbits[offssymbol] > 4) {
            if (!rar_br_read_ahead(a, br, offsetbits[offssymbol] - 4))
              goto truncated_data;
            offs += rar_br_bits(br, offsetbits[offssymbol] - 4) << 4;
            rar_br_consume(br, offsetbits[offssymbol] - 4);
	  }

          if(rar->numlowoffsetrepeats > 0)
          {
            rar->numlowoffsetrepeats--;
            offs += rar->lastlowoffset;
          }
          else
          {
            if ((lowoffsetsymbol =
              read_next_symbol(a, &rar->lowoffsetcode)) < 0)
              return (ARCHIVE_FATAL);
            if(lowoffsetsymbol == 16)
            {
              rar->numlowoffsetrepeats = 15;
              offs += rar->lastlowoffset;
            }
            else
            {
              offs += lowoffsetsymbol;
              rar->lastlowoffset = lowoffsetsymbol;
            }
          }
        }
        else {
          if (!rar_br_read_ahead(a, br, offsetbits[offssymbol]))
            goto truncated_data;
          offs += rar_br_bits(br, offsetbits[offssymbol]);
          rar_br_consume(br, offsetbits[offssymbol]);
        }
      }

      if (offs >= 0x40000)
        len++;
      if (offs >= 0x2000)
        len++;

      for(i = 3; i > 0; i--)
        rar->oldoffset[i] = rar->oldoffset[i-1];
      rar->oldoffset[0] = offs;
    }

    rar->lastoffset = offs;
    rar->lastlength = len;
    rar->output_last_match = 1;
  }