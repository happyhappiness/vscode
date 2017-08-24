(!haveNewline && leftToRead != 0 &&
         (static_cast<void>(is.clear(is.rdstate() & ~std::ios::failbit)),
          static_cast<void>(is.getline(buffer, bufferSize)),
          is.gcount() > 0)) {
    // We have read at least one byte.
    haveData = true;

    // If newline character was read the gcount includes the character
    // but the buffer does not: the end of line has been reached.
    size_t length = strlen(buffer);
    if (length < static_cast<size_t>(is.gcount())) {
      haveNewline = true;
    }

    // Avoid storing a carriage return character.
    if (length > 0 && buffer[length - 1] == '\r') {
      buffer[length - 1] = 0;
    }

    // if we read too much then truncate the buffer
    if (leftToRead > 0) {
      if (static_cast<long>(length) > leftToRead) {
        buffer[leftToRead] = 0;
        leftToRead = 0;
      } else {
        leftToRead -= static_cast<long>(length);
      }
    }

    // Append the data read to the line.
    line.append(buffer);
  }