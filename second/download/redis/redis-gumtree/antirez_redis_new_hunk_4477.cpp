    if (line[0] != prefix_int_reply)
      throw protocol_error("unexpected prefix for integer reply");

    return value_from_string<client::int_type>(line.substr(1));
  }

  void client::recv_int_ok_reply_()
