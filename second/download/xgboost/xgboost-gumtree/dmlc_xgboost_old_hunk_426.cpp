      unsigned long amount;
      if (sscanf(val, "%lu%c", &amount, &unit) == 2) {
        switch (unit) {
          case 'B': reduce_buffer_size = amount; break;
          case 'K': reduce_buffer_size = amount << 10UL; break;
          case 'M': reduce_buffer_size = amount << 20UL; break;
          case 'G': reduce_buffer_size = amount << 30UL; break;
          default: utils::Error("invalid format for reduce buffer");
        }
      } else {
