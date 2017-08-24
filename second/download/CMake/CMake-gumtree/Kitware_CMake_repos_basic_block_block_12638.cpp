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