(bg_bright != -1) {
    if (bg_bright) {
      info.wAttributes |= BACKGROUND_INTENSITY;
    } else {
      info.wAttributes &= ~BACKGROUND_INTENSITY;
    }
  }