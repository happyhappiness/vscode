{
    info.wAttributes &= ~(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
    if (bg_color & 1) info.wAttributes |= BACKGROUND_RED;
    if (bg_color & 2) info.wAttributes |= BACKGROUND_GREEN;
    if (bg_color & 4) info.wAttributes |= BACKGROUND_BLUE;
  }