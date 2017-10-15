
      rpc::call_command("d.directory.set", rak::trim(input->str()), rpc::make_target(*current_view()->focus()));
      control->core()->push_log_std("New root directory \"" + rpc::call_command_string("d.directory", rpc::make_target(*current_view()->focus())) + "\" for torrent.");
      break;

    case INPUT_COMMAND:
      rpc::parse_command_single(current_view()->focus() != current_view()->end_visible() ?
                                rpc::make_target(*current_view()->focus()) : rpc::make_target(),
                                input->str());
      break;

    default:
      throw torrent::internal_error("DownloadList::receive_exit_input(...) Invalid input type.");
    }

