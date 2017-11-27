static int get_memory_machine_checks(void) {
  static const char dump[] = "dump all bios\n";
  int ret = socket_adapter.write(&socket_adapter, dump, sizeof(dump));
  if (ret != 0)
    ERROR(MCELOG_PLUGIN ": SENT DUMP REQUEST FAILED");
  else
    DEBUG(MCELOG_PLUGIN ": SENT DUMP REQUEST OK");
  return ret;
}