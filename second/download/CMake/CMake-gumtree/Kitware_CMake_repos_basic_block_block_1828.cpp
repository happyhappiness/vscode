{
    this->CurrentPositionInFile = pos;
    pos = buffer.find(":", pos);
    size_t pos2 = buffer.find("\n", pos);
    if (pos != std::string::npos && pos2 != std::string::npos) {
      // It may happen that the beginning matches, but this is still not the
      // requested key.
      // An example is looking for "cpu" when "cpu family" comes first. So we
      // check that
      // we have only spaces from here to pos, otherwise we search again.
      for (size_t i = this->CurrentPositionInFile + strlen(word); i < pos;
           ++i) {
        if (buffer[i] != ' ' && buffer[i] != '\t') {
          return this->ExtractValueFromCpuInfoFile(buffer, word, pos2);
        }
      }
      return buffer.substr(pos + 2, pos2 - pos - 2);
    }
  }