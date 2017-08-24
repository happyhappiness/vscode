{
    is_absolute = target_len >= 3 && IS_LETTER(path[0]) &&
      path[1] == L':' && IS_SLASH(path[2]);
  }