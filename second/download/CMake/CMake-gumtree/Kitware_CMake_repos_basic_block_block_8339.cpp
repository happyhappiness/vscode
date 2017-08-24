(unicode >= 0xD800 && unicode <= 0xDBFF) {
    // surrogate pairs
    if (end - current < 6)
      return addError(
          "additional six characters expected to parse unicode surrogate pair.",
          token,
          current);
    unsigned int surrogatePair;
    if (*(current++) == '\\' && *(current++) == 'u') {
      if (decodeUnicodeEscapeSequence(token, current, end, surrogatePair)) {
        unicode = 0x10000 + ((unicode & 0x3FF) << 10) + (surrogatePair & 0x3FF);
      } else
        return false;
    } else
      return addError("expecting another \\u token to begin the second half of "
                      "a unicode surrogate pair",
                      token,
                      current);
  }