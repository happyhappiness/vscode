(i = 0; i < slots; i++, a->format++) {
    if (!a->format->name || !strcmp(a->format->name, str))
      break;
  }