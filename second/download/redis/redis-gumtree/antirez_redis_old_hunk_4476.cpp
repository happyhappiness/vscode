    if (line[0] != prefix)
      throw protocol_error("unexpected prefix for bulk reply");

    return number_from_string(line.substr(1));
  }

  string client::recv_bulk_reply_() 
