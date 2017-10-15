  first = print_buffer(first, last, " [%c%c R: %4.2f",
                       rpc::call_command_string("d.get_tied_to_file", rpc::make_target(d)).empty() ? ' ' : 'T',
                       rpc::call_command_value("d.get_ignore_commands", rpc::make_target(d)) == 0 ? ' ' : 'I',
                       (double)rpc::call_command_value("d.get_ratio", rpc::make_target(d)) / 1000.0);

  if (d->priority() != 2)
    first = print_buffer(first, last, " %s]", rpc::call_command_string("d.get_priority_str", rpc::make_target(d)).c_str());
  else
    first = print_buffer(first, last, "]");

  if (first > last)
    throw torrent::internal_error("print_download_info(...) wrote past end of the buffer.");

  return first;
}
