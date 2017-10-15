print_buffer(first, last, " [%c%c R: %3.2f",
                       rpc::call_command_d_string("get_d_tied_to_file", d).empty() ? ' ' : 'T',
                       rpc::call_command_d_value("get_d_ignore_commands", d) == 0 ? ' ' : 'I',
                       d->download()->bytes_done() > 0 ? (double)(100 * d->download()->up_rate()->total() / d->download()->bytes_done()) / 100 : 0.0);