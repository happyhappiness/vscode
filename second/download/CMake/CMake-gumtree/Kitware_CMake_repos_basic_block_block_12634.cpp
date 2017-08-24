f(lengthbits[symbol-271] > 0) {
        if (!rar_br_read_ahead(a, br, lengthbits[symbol-271]))
          goto truncated_data;
        len += rar_br_bits(br, lengthbits[symbol-271]);
        rar_br_consume(br, lengthbits[symbol-271]);
      }