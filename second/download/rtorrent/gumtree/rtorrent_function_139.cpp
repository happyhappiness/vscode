char*
print_download_time_left(char* first, char* last, core::Download* d) {
  uint32_t rate = d->get_download().down_rate()->rate();

  if (rate < 512)
    return print_buffer(first, last, "--:--:--");
  
  time_t remaining = (d->get_download().bytes_total() - d->get_download().bytes_done()) / (rate & ~(uint32_t)(512 - 1));

  return print_ddhhmm(first, last, remaining);
}