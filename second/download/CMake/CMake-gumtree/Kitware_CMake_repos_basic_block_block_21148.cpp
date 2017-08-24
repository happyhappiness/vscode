{
  unsigned short argc = handle->tty.wr.ansi_csi_argc;
  unsigned short* argv = handle->tty.wr.ansi_csi_argv;
  int i;
  CONSOLE_SCREEN_BUFFER_INFO info;

  char fg_color = -1, bg_color = -1;
  char fg_bright = -1, bg_bright = -1;
  char inverse = -1;

  if (argc == 0) {
    /* Reset mode */
    fg_color = uv_tty_default_fg_color;
    bg_color = uv_tty_default_bg_color;
    fg_bright = uv_tty_default_fg_bright;
    bg_bright = uv_tty_default_bg_bright;
    inverse = uv_tty_default_inverse;
  }

  for (i = 0; i < argc; i++) {
    short arg = argv[i];

    if (arg == 0) {
      /* Reset mode */
      fg_color = uv_tty_default_fg_color;
      bg_color = uv_tty_default_bg_color;
      fg_bright = uv_tty_default_fg_bright;
      bg_bright = uv_tty_default_bg_bright;
      inverse = uv_tty_default_inverse;

    } else if (arg == 1) {
      /* Foreground bright on */
      fg_bright = 1;

    } else if (arg == 2) {
      /* Both bright off */
      fg_bright = 0;
      bg_bright = 0;

    } else if (arg == 5) {
      /* Background bright on */
      bg_bright = 1;

    } else if (arg == 7) {
      /* Inverse: on */
      inverse = 1;

    } else if (arg == 21 || arg == 22) {
      /* Foreground bright off */
      fg_bright = 0;

    } else if (arg == 25) {
      /* Background bright off */
      bg_bright = 0;

    } else if (arg == 27) {
      /* Inverse: off */
      inverse = 0;

    } else if (arg >= 30 && arg <= 37) {
      /* Set foreground color */
      fg_color = arg - 30;

    } else if (arg == 39) {
      /* Default text color */
      fg_color = uv_tty_default_fg_color;
      fg_bright = uv_tty_default_fg_bright;

    } else if (arg >= 40 && arg <= 47) {
      /* Set background color */
      bg_color = arg - 40;

    } else if (arg ==  49) {
      /* Default background color */
      bg_color = uv_tty_default_bg_color;
      bg_bright = uv_tty_default_bg_bright;

    } else if (arg >= 90 && arg <= 97) {
      /* Set bold foreground color */
      fg_bright = 1;
      fg_color = arg - 90;

    } else if (arg >= 100 && arg <= 107) {
      /* Set bold background color */
      bg_bright = 1;
      bg_color = arg - 100;

    }
  }

  if (fg_color == -1 && bg_color == -1 && fg_bright == -1 &&
      bg_bright == -1 && inverse == -1) {
    /* Nothing changed */
    return 0;
  }

  if (!GetConsoleScreenBufferInfo(handle->handle, &info)) {
    *error = GetLastError();
    return -1;
  }

  if ((info.wAttributes & COMMON_LVB_REVERSE_VIDEO) > 0) {
    FLIP_FGBG;
  }

  if (fg_color != -1) {
    info.wAttributes &= ~(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    if (fg_color & 1) info.wAttributes |= FOREGROUND_RED;
    if (fg_color & 2) info.wAttributes |= FOREGROUND_GREEN;
    if (fg_color & 4) info.wAttributes |= FOREGROUND_BLUE;
  }

  if (fg_bright != -1) {
    if (fg_bright) {
      info.wAttributes |= FOREGROUND_INTENSITY;
    } else {
      info.wAttributes &= ~FOREGROUND_INTENSITY;
    }
  }

  if (bg_color != -1) {
    info.wAttributes &= ~(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
    if (bg_color & 1) info.wAttributes |= BACKGROUND_RED;
    if (bg_color & 2) info.wAttributes |= BACKGROUND_GREEN;
    if (bg_color & 4) info.wAttributes |= BACKGROUND_BLUE;
  }

  if (bg_bright != -1) {
    if (bg_bright) {
      info.wAttributes |= BACKGROUND_INTENSITY;
    } else {
      info.wAttributes &= ~BACKGROUND_INTENSITY;
    }
  }

  if (inverse != -1) {
    if (inverse) {
      info.wAttributes |= COMMON_LVB_REVERSE_VIDEO;
    } else {
      info.wAttributes &= ~COMMON_LVB_REVERSE_VIDEO;
    }
  }

  if ((info.wAttributes & COMMON_LVB_REVERSE_VIDEO) > 0) {
    FLIP_FGBG;
  }

  if (!SetConsoleTextAttribute(handle->handle, info.wAttributes)) {
    *error = GetLastError();
    return -1;
  }

  return 0;
}