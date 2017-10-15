
char*
print_download_time_left(char* first, char* last, core::Download* d) {
  uint32_t rate = d->download()->down_rate()->rate();

  if (rate < 512)
    return print_buffer(first, last, "--d --:--");
  
  time_t remaining = (d->download()->bytes_total() - d->download()->bytes_done()) / (rate & ~(uint32_t)(512 - 1));

  return print_ddhhmm(first, last, remaining);
}

