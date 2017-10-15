print_buffer(first, last, " [%c%c R: %4.2f",
                       rpc::call_command_string("d.tied_to_file", rpc::make_target(d)).empty() ? ' ' : 'T',
                       rpc::call_command_value("d.ignore_commands", rpc::make_target(d)) == 0 ? ' ' : 'I',
                       (double)rpc::call_command_value("d.ratio", rpc::make_target(d)) / 1000.0);