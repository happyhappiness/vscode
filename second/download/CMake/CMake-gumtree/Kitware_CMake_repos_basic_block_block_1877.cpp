(int i = 0; i < 6; ++i) {
        if (!have[i] && sscanf(buffer, format[i], &value[i]) == 1) {
          have[i] = true;
          ++count;
        }
      }