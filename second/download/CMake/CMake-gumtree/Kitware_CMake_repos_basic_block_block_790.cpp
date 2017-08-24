(ones == 1 && lstate.buffered == 0) {
      // This is a continuation of a codepoint that never started.
      return std::codecvt_base::error;
    }