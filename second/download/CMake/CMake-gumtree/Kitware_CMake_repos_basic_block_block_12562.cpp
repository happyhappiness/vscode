f(val == 16) {
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