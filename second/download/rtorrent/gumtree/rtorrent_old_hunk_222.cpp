    switch (type) {
    case INPUT_NONE:
      break;

    case INPUT_LOAD_DEFAULT:
    case INPUT_LOAD_MODIFIED:
      control->core()->try_create_download_expand(input->str(), type == INPUT_LOAD_DEFAULT);
      break;

    case INPUT_CHANGE_DIRECTORY:
      if (current_view()->focus() == current_view()->end_visible())
        throw torrent::input_error("No download in focus to change root directory.");

      rpc::call_command_d("set_d_directory", *current_view()->focus(), rak::trim(input->str()));
      control->core()->push_log("New root directory \"" + rpc::call_command_d_string("get_d_directory", *current_view()->focus()) + "\" for torrent.");
      break;

    case INPUT_COMMAND:
      rpc::parse_command_single_std(input->str());
      break;

    default:
      throw torrent::internal_error("DownloadList::receive_exit_input(...) Invalid input type.");
    }

