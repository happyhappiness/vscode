const char *opcode_str(int o) {
  static char buf[30];
  switch (o) {
  case 0:
    return "Query";
  case 1:
    return "Iquery";
  case 2:
    return "Status";
  case 4:
    return "Notify";
  case 5:
    return "Update";
  default:
    ssnprintf(buf, sizeof(buf), "Opcode%d", o);
    return buf;
  }
}