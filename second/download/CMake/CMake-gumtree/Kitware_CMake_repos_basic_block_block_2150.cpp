(static_cast<std::streamsize>(finSource.gcount()) != nnext ||
        static_cast<std::streamsize>(finDestination.gcount()) != nnext) {
      return true;
    }