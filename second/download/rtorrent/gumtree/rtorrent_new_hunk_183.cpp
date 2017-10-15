
  } else {
    *first = '\0';
  }

  if (first > last)
    throw torrent::internal_error("print_download_status(...) wrote past end of the buffer.");

  return first;
}

char*
print_download_time_left(char* first, char* last, core::Download* d) {
  uint32_t rate = d->download()->down_rate()->rate();

  if (rate < 512)
    return print_buffer(first, last, "--d --:--");
  
  time_t remaining = (d->download()->file_list()->size_bytes() - d->download()->bytes_done()) / (rate & ~(uint32_t)(512 - 1));

  return print_ddhhmm(first, last, remaining);
}

char*
print_download_percentage_done(char* first, char* last, core::Download* d) {
  if (!d->is_open() || d->is_done())
    //return print_buffer(first, last, "[--%%]");
    return print_buffer(first, last, "     ");
  else
    return print_buffer(first, last, "[%2u%%]", (d->download()->file_list()->completed_chunks() * 100) / d->download()->file_list()->size_chunks());
}

char*
print_client_version(char* first, char* last, const torrent::ClientInfo& clientInfo) {
  switch (torrent::ClientInfo::version_size(clientInfo.type())) {
  case 4:
    return print_buffer(first, last, "%s %hhu.%hhu.%hhu.%hhu",
                        clientInfo.short_description(),
                        clientInfo.version()[0], clientInfo.version()[1],
                        clientInfo.version()[2], clientInfo.version()[3]);
  case 3:
    return print_buffer(first, last, "%s %hhu.%hhu.%hhu",
                        clientInfo.short_description(),
                        clientInfo.version()[0], clientInfo.version()[1],
                        clientInfo.version()[2]);
  default:
    return print_buffer(first, last, "%s", clientInfo.short_description());
  }
}

char*
print_status_info(char* first, char* last) {
  if (torrent::up_throttle() == 0)
    first = print_buffer(first, last, "[Throttle off");
