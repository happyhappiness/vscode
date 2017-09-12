    if (line[0] != prefix_int_reply)
      throw protocol_error("unexpected prefix for integer reply");

    return number_from_string(line.substr(1));
  }

  void client::recv_int_ok_reply_()
