       break;
 
     case INPUT_CHANGE_DIRECTORY:
       if (current_view()->focus() == current_view()->end_visible())
         throw torrent::input_error("No download in focus to change root directory.");
 
-      rpc::call_command_d("d.set_directory", *current_view()->focus(), rak::trim(input->str()));
-      control->core()->push_log_std("New root directory \"" + rpc::call_command_d_string("d.get_directory", *current_view()->focus()) + "\" for torrent.");
+      if ((*current_view()->focus())->is_open())
+        throw torrent::input_error("Cannot change root directory on an open download.");
+
+      rpc::call_command("d.set_directory", rak::trim(input->str()), rpc::make_target(*current_view()->focus()));
+      control->core()->push_log_std("New root directory \"" + rpc::call_command_string("d.get_directory", rpc::make_target(*current_view()->focus())) + "\" for torrent.");
       break;
 
     case INPUT_COMMAND:
       rpc::parse_command_d_single_std(current_view()->focus() != current_view()->end_visible() ? *current_view()->focus() : NULL, input->str());
       break;
 
