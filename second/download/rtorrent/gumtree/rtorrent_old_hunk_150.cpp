      resume(download);

    break;

  case Download::variable_hashing_last:

    if (download->is_done())
      confirm_finished(download);
    else
      download->set_message("Hash check on download completion found bad chunks.");
    
    break;

  case Download::variable_hashing_stopped:
  default:
    // Either an error or someone wrote to the hashing variable...
