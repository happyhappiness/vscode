     first = print_download_time_left(first, last, d);
   } else {
     first = print_buffer(first, last, "                ");
   }
 
   first = print_buffer(first, last, " [%c%c R: %3.2f",
-                       d->get_string("tied_to_file").empty() ? ' ' : 'T',
-                       d->get_value("ignore_commands") == 0 ? ' ' : 'I',
+                       rpc::call_command_d_string("get_d_tied_to_file", d).empty() ? ' ' : 'T',
+                       rpc::call_command_d_value("get_d_ignore_commands", d) == 0 ? ' ' : 'I',
                        d->download()->bytes_done() > 0 ? (double)(100 * d->download()->up_rate()->total() / d->download()->bytes_done()) / 100 : 0.0);
 
   if (d->priority() != 2)
     first = print_buffer(first, last, " %s]", core::Download::priority_to_string(d->priority()));
   else
     first = print_buffer(first, last, "]");
