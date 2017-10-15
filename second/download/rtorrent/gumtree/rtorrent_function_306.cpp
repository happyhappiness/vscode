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

  first = print_buffer(first, last, " [%c%c R: %4.2f",
                       rpc::call_command_d_string("d.get_tied_to_file", d).empty() ? ' ' : 'T',
                       rpc::call_command_d_value("d.get_ignore_commands", d) == 0 ? ' ' : 'I',
                       (double)rpc::call_command_d_value("d.get_ratio", d) / 1000.0);

  if (d->priority() != 2)
    first = print_buffer(first, last, " %s]", rpc::call_command_d_string("d.get_priority_str", d).c_str());
  else
    first = print_buffer(first, last, "]");

  if (first > last)
    throw torrent::internal_error("print_download_info(...) wrote past end of the buffer.");

  return first;
}