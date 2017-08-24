(static_cast<long>(length) > leftToRead) {
        buffer[leftToRead] = 0;
        leftToRead = 0;
      } else {
        leftToRead -= static_cast<long>(length);
      }