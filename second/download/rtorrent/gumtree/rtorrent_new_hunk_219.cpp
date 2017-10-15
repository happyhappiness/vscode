    first = print_buffer(first, last, " ");
    first = print_download_time_left(first, last, d);
  } else {
    first = print_buffer(first, last, "                ");
  }

  first = print_buffer(first, last, " [%c%c R: %4.2f",
                       rpc::call_command_d_string("get_d_tied_to_file", d).empty() ? ' ' : 'T',
                       rpc::call_command_d_value("get_d_ignore_commands", d) == 0 ? ' ' : 'I',
                       (double)rpc::call_command_d_value("get_d_ratio", d) / 1000.0);

  if (d->priority() != 2)
    first = print_buffer(first, last, " %s]", rpc::call_command_d_string("get_d_priority_str", d).c_str());
  else
    first = print_buffer(first, last, "]");

  if (first > last)
    throw torrent::internal_error("print_download_info(...) wrote past end of the buffer.");

