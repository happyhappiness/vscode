print_buffer(first, last, " [%c%c R: %3.2f",
                       d->variable()->get_string("tied_to_file").empty() ? ' ' : 'T',
                       d->variable()->get_value("ignore_commands") == 0 ? ' ' : 'I',
                       d->download()->bytes_done() > 0 ? (double)(100 * d->download()->up_rate()->total() / d->download()->bytes_done()) / 100 : 0.0);