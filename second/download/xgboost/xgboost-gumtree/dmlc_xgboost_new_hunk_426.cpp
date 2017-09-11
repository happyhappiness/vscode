      unsigned long amount;
      if (sscanf(val, "%lu%c", &amount, &unit) == 2) {
        switch (unit) {
          case 'B': reduce_buffer_size = (amount + 7)/ 8; break;
          case 'K': reduce_buffer_size = amount << 7UL; break;
          case 'M': reduce_buffer_size = amount << 17UL; break;
          case 'G': reduce_buffer_size = amount << 27UL; break;
          default: utils::Error("invalid format for reduce buffer");
        }
      } else {
