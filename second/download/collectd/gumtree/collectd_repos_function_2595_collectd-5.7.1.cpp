static void exit_usage(int status) {
  printf("Usage: " PACKAGE_NAME " [OPTIONS]\n\n"

         "Available options:\n"
         "  General:\n"
         "    -C <file>       Configuration file.\n"
         "                    Default: " CONFIGFILE "\n"
         "    -t              Test config and exit.\n"
         "    -T              Test plugin read and exit.\n"
         "    -P <file>       PID-file.\n"
         "                    Default: " PIDFILE "\n"
#if COLLECT_DAEMON
         "    -f              Don't fork to the background.\n"
#endif
         "    -h              Display help (this message)\n"
         "\nBuiltin defaults:\n"
         "  Config file       " CONFIGFILE "\n"
         "  PID file          " PIDFILE "\n"
         "  Plugin directory  " PLUGINDIR "\n"
         "  Data directory    " PKGLOCALSTATEDIR "\n"
         "\n" PACKAGE_NAME " " PACKAGE_VERSION ", http://collectd.org/\n"
         "by Florian octo Forster <octo@collectd.org>\n"
         "for contributions see `AUTHORS'\n");
  exit(status);
}