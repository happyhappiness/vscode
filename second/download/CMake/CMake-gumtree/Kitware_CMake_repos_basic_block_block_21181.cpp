{
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