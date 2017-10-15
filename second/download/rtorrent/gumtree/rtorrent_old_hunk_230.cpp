      break;

    case INPUT_CHANGE_DIRECTORY:
      if (current_view()->focus() == current_view()->end_visible())
        throw torrent::input_error("No download in focus to change root directory.");

      rpc::call_command_d("set_d_directory", *current_view()->focus(), rak::trim(input->str()));
      control->core()->push_log_std("New root directory \"" + rpc::call_command_d_string("get_d_directory", *current_view()->focus()) + "\" for torrent.");
      break;

    case INPUT_COMMAND:
      rpc::parse_command_d_single_std(current_view()->focus() != current_view()->end_visible() ? *current_view()->focus() : NULL, input->str());
      break;

