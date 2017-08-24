(bytesWrittenMore > 0) {
      bytesWrittenTotal += bytesWrittenMore;
      if (bytesWrittenTotal >= count)
        success = 1;
    }