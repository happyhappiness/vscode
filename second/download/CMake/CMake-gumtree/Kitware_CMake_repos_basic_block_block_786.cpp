(from_next != from_end) {
    // Count leading ones in the bits of the next byte.
    unsigned char const ones =
      cm_utf8_ones[static_cast<unsigned char>(*from_next)];

    if (ones != 1 && lstate.buffered != 0) {
      // We have a buffered partial codepoint that we never completed.
      return std::codecvt_base::error;
    } else if (ones == 1 && lstate.buffered == 0) {
      // This is a continuation of a codepoint that never started.
      return std::codecvt_base::error;
    }

    // Compute the number of bytes in the current codepoint.
    int need = 0;
    switch (ones) {
      case 0: // 0xxx xxxx: new codepoint of size 1
        need = 1;
        break;
      case 1: // 10xx xxxx: continues a codepoint
        assert(lstate.size != 0);
        need = lstate.size;
        break;
      case 2: // 110x xxxx: new codepoint of size 2
        need = 2;
        break;
      case 3: // 1110 xxxx: new codepoint of size 3
        need = 3;
        break;
      case 4: // 1111 0xxx: new codepoint of size 4
        need = 4;
        break;
      default: // invalid byte
        return std::codecvt_base::error;
    }
    assert(need > 0);

    if (lstate.buffered + 1 == need) {
      // This byte completes a codepoint.
      std::codecvt_base::result decode_result =
        this->Decode(state, need, from_next, to_next, to_end);
      if (decode_result != std::codecvt_base::ok) {
        return decode_result;
      }
    } else {
      // This byte does not complete a codepoint.
      this->BufferPartial(state, need, from_next);
    }
  }