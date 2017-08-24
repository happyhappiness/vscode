{
  size_t pos = this->SysCtlBuffer.find(word);
  if (pos != std::string::npos) {
    pos = this->SysCtlBuffer.find(": ", pos);
    size_t pos2 = this->SysCtlBuffer.find("\n", pos);
    if (pos != std::string::npos && pos2 != std::string::npos) {
      return this->SysCtlBuffer.substr(pos + 2, pos2 - pos - 2);
    }
  }
  return "";
}