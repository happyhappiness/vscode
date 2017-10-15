print_buffer(first, last, " [%c%c R: %4.2f",
                       rpc::call_command_string("d.get_tied_to_file", rpc::make_target(d)).empty() ? ' ' : 'T',
                       rpc::call_command_value("d.get_ignore_commands", rpc::make_target(d)) == 0 ? ' ' : 'I',
                       (double)rpc::call_command_value("d.get_ratio", rpc::make_target(d)) / 1000.0);