static void exit_usage(int exit_status) /* {{{ */
{
  fprintf(
      (exit_status == EXIT_FAILURE) ? stderr : stdout,
      "collectd-tg -- collectd traffic generator\n"
      "\n"
      "  Usage: collectd-ng [OPTION]\n"
      "\n"
      "  Valid options:\n"
      "    -n <number>    Number of value lists. (Default: %i)\n"
      "    -H <number>    Number of hosts to emulate. (Default: %i)\n"
      "    -p <number>    Number of plugins to emulate. (Default: %i)\n"
      "    -i <seconds>   Interval of each value in seconds. (Default: %.3f)\n"
      "    -d <dest>      Destination address of the network packets.\n"
      "                   (Default: %s)\n"
      "    -D <port>      Destination port of the network packets.\n"
      "                   (Default: %s)\n"
      "    -h             Print usage information (this output).\n"
      "\n"
      "Copyright (C) 2010-2012  Florian Forster\n"
      "Licensed under the MIT license.\n",
      DEF_NUM_VALUES, DEF_NUM_HOSTS, DEF_NUM_PLUGINS, DEF_INTERVAL,
      NET_DEFAULT_V6_ADDR, NET_DEFAULT_PORT);
  exit(exit_status);
}