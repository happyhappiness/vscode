  }
}




void setup_protocol(void)
{
  if (remote_version == 10) {
    send_file_entry = send_file_entry_v10;
    receive_file_entry = receive_file_entry_v10;
  } else {
    send_file_entry = send_file_entry_v11;
    receive_file_entry = receive_file_entry_v11;
  }
}

