static int load_config(const char *key, const char *value) {
  if (strcasecmp(key, "ReportRelative") == 0)
#ifdef _SC_NPROCESSORS_ONLN
    report_relative_load = IS_TRUE(value) ? 1 : 0;
#else
    WARNING("load plugin: The \"ReportRelative\" configuration "
            "is not available, because I can't determine the "
            "number of CPUS on this system. Sorry.");
#endif
  return -1;
}