{
    /* If suddenly find the cursor outside of the virtual window, it must */
    /* have somehow scrolled. Update the virtual window offset. */
    uv_tty_virtual_offset = info->dwCursorPosition.Y -
                            uv_tty_virtual_height + 1;
  }