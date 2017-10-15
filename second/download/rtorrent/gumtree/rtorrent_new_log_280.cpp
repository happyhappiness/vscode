print_buffer(first, last, " [%c%c R: %4.2f",
                       rpc::call_command_d_string("get_d_tied_to_file", d).empty() ? ' ' : 'T',
                       rpc::call_command_d_value("get_d_ignore_commands", d) == 0 ? ' ' : 'I',
                       (double)rpc::call_command_d_value("get_d_ratio", d) / 1000.0);