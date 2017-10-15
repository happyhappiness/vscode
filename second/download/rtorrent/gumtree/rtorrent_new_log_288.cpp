print_buffer(first, last, " [%c%c R: %4.2f",
                       rpc::call_command_d_string("d.get_tied_to_file", d).empty() ? ' ' : 'T',
                       rpc::call_command_d_value("d.get_ignore_commands", d) == 0 ? ' ' : 'I',
                       (double)rpc::call_command_d_value("d.get_ratio", d) / 1000.0);