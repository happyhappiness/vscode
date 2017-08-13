bool Reader::decodeDouble(Token& token, Value& decoded) {
  double value = 0;
  const int bufferSize = 32;
  int count;
  int length = int(token.end_ - token.start_);

  // Sanity check to avoid buffer overflow exploits.
  if (length < 0) {
    return addError("Unable to parse token length", token);
  }

  // Avoid using a string constant for the format control string given to
  // sscanf, as this can cause hard to debug crashes on OS X. See here for more
  // info:
  //
  //     http://developer.apple.com/library/mac/#DOCUMENTATION/DeveloperTools/gcc-4.0.1/gcc/Incompatibilities.html
  char format[] = "%lf";

  if (length <= bufferSize) {
    Char buffer[bufferSize + 1];
    memcpy(buffer, token.start_, length);
    buffer[length] = 0;
    count = sscanf(buffer, format, &value);
  } else {
    std::string buffer(token.start_, token.end_);
    count = sscanf(buffer.c_str(), format, &value);
  }

  if (count != 1)
    return addError("'" + std::string(token.start_, token.end_) +
                        "' is not a number.",
                    token);
  decoded = value;
  return true;
}