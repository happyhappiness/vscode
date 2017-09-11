inline size_t ParseUnit(const char *name, const char *val) {
  char unit;
  uint64_t amount;
  int n = sscanf(val, "%lu%c", &amount, &unit);
  if (n == 2) {
    switch (unit) {
      case 'B': return amount;
      case 'K': return amount << 10UL;
      case 'M': return amount << 20UL;
      case 'G': return amount << 30UL;
      default: utils::Error("invalid format for %s", name); return 0;
    }
  } else if (n == 1) {
    return amount;
  } else {
    utils::Error("invalid format for %s,"                               \
                 "shhould be {integer}{unit}, unit can be {B, KB, MB, GB}", name);
    return 0;
  }
}