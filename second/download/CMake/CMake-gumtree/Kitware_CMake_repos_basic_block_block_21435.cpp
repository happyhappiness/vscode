(path[len - 1] == L'\\' &&
      !(len == 3 && path[1] == L':')) {
    len--;
    path[len] = L'\0';
  }