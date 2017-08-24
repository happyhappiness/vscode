(lengthbits[lensymbol] > 0) {
        if (!rar_br_read_ahead(a, br, lengthbits[lensymbol]))
          goto truncated_data;
        len += rar_br_bits(br, lengthbits[lensymbol]);
        rar_br_consume(br, lengthbits[lensymbol]);
      }