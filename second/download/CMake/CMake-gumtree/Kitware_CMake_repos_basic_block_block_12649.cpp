{
        rar->start_new_block = 1;
        if (!rar_br_read_ahead(a, br, 1))
          goto truncated_data;
        rar->start_new_table = rar_br_bits(br, 1);
        rar_br_consume(br, 1);
        return lzss_position(&rar->lzss);
      }