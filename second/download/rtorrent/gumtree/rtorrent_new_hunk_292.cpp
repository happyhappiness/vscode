      if (current_view()->focus() == current_view()->end_visible())
        throw torrent::input_error("No download in focus to change root directory.");

      if ((*current_view()->focus())->is_open())
        throw torrent::input_error("Cannot change root directory on an open download.");

      rpc::call_command("d.directory.set", rak::trim(input->str()), rpc::make_target(*current_view()->focus()));
      control->core()->push_log_std("New root directory \"" + rpc::call_command_string("d.directory", rpc::make_target(*current_view()->focus())) + "\" for torrent.");
      break;

    case INPUT_COMMAND:
      rpc::parse_command_d_single_std(current_view()->focus() != current_view()->end_visible() ? *current_view()->focus() : NULL, input->str());
      break;

