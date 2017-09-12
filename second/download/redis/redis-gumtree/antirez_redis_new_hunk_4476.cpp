    if (line[0] != prefix)
      throw protocol_error("unexpected prefix for bulk reply");

    return value_from_string<client::int_type>(line.substr(1));
  }

  string client::recv_bulk_reply_() 
