inline void SetParam(const char *name, const char *val) {
    if (!strcmp(name, "master_uri")) master_uri = val;
    if (!strcmp(name, "master_port")) master_port = atoi(val);
    if (!strcmp(name, "reduce_buffer")) {
      char unit;
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
        utils::Error("invalid format for reduce_buffer, shhould be {integer}{unit}, unit can be {B, KB, MB, GB}");
      }
    }
  }