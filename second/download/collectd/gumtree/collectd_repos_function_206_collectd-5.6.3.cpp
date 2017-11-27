static void exit_usage(const char *name, int status) {
  fprintf(
      (status == 0) ? stdout : stderr,
      "Usage: %s [options] <command> [cmd options]\n\n"

      "Available options:\n"
      "  -s       Path to collectd's UNIX socket.\n"
      "           Default: " DEFAULT_SOCK "\n"

      "\n  -h       Display this help and exit.\n"

      "\nAvailable commands:\n\n"

      " * getval <identifier>\n"
      " * flush [timeout=<seconds>] [plugin=<name>] [identifier=<id>]\n"
      " * listval\n"
      " * putval <identifier> [interval=<seconds>] <value-list(s)>\n"

      "\nIdentifiers:\n\n"

      "An identifier has the following format:\n\n"

      "  [<hostname>/]<plugin>[-<plugin_instance>]/<type>[-<type_instance>]\n\n"

      "Hostname defaults to the local hostname if omitted (e.g., "
      "uptime/uptime).\n"
      "No error is returned if the specified identifier does not exist.\n"

      "\n" PACKAGE_NAME " " PACKAGE_VERSION ", http://collectd.org/\n"
      "by Florian octo Forster <octo@collectd.org>\n"
      "for contributions see `AUTHORS'\n",
      name);
  exit(status);
}