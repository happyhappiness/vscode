{
    pos2 = buffer.find(" ", pos2 + 1);
    if (pos2 != std::string::npos && pos2 < pos3) {
      this->ChipID.Revision =
        atoi(buffer.substr(pos2 + 1, pos3 - pos2).c_str());
    }
  }