char*
print_download_info(char* first, char* last, core::Download* d) {
  if (!d->download()->is_open())
    first = print_buffer(first, last, "[CLOSED]  ");
  else if (!d->download()->is_active())
    first = print_buffer(first, last, "[OPEN]    ");
  else
    first = print_buffer(first, last, "          ");

  if (d->is_done())
    first = print_buffer(first, last, "done %10.1f MB", (double)d->download()->file_list()->size_bytes() / (double)(1 << 20));
  else
    first = print_buffer(first, last, "%6.1f / %6.1f MB",
                         (double)d->download()->bytes_done() / (double)(1 << 20),
                         (double)d->download()->file_list()->size_bytes() / (double)(1 << 20));
  
  first = print_buffer(first, last, " Rate: %5.1f / %5.1f KB Uploaded: %7.1f MB",
                       (double)d->download()->up_rate()->rate() / (1 << 10),
                       (double)d->download()->down_rate()->rate() / (1 << 10),
                       (double)d->download()->up_rate()->total() / (1 << 20));

  if (d->download()->is_active() && !d->is_done()) {
    first = print_buffer(first, last, " ");
    first = print_download_percentage_done(first, last, d);

    first = print_buffer(first, last, " ");
    first = print_download_time_left(first, last, d);
  } else {
    first = print_buffer(first, last, "                ");
  }

  first = print_buffer(first, last, " [%c%c R: %3.2f",
                       rpc::call_command_d_string("get_d_tied_to_file", d).empty() ? ' ' : 'T',
                       rpc::call_command_d_value("get_d_ignore_commands", d) == 0 ? ' ' : 'I',
                       d->download()->bytes_done() > 0 ? (double)(100 * d->download()->up_rate()->total() / d->download()->bytes_done()) / 100 : 0.0);

  if (d->priority() != 2)
    first = print_buffer(first, last, " %s]", core::Download::priority_to_string(d->priority()));
  else
    first = print_buffer(first, last, "]");

  if (first > last)
    throw torrent::internal_error("print_download_info(...) wrote past end of the buffer.");

  return first;
}