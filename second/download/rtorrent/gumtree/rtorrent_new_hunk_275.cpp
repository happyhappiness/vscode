    return print_buffer(first, last, "%s", clientInfo.short_description());
  }
}

char*
print_status_info(char* first, char* last) {
  if (!torrent::up_throttle_global()->is_throttled())
    first = print_buffer(first, last, "[Throttle off");
  else
    first = print_buffer(first, last, "[Throttle %3i", torrent::up_throttle_global()->max_rate() / 1024);

  if (!torrent::down_throttle_global()->is_throttled())
    first = print_buffer(first, last, "/off KB]");
  else
    first = print_buffer(first, last, "/%3i KB]", torrent::down_throttle_global()->max_rate() / 1024);
  
  first = print_buffer(first, last, " [Rate %5.1f/%5.1f KB]",
                       (double)torrent::up_rate()->rate() / 1024.0,
