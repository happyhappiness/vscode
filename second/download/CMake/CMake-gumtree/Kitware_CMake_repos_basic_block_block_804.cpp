{
    msg = mf->FormatListFileStack();
    if (!msg.empty()) {
      msg = "\n   Called from: " + msg;
    }
  }