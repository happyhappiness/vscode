(!SetConsoleMode(handle, dwMode)) {
    uv__vterm_state = UV_UNSUPPORTED;
    return;
  }