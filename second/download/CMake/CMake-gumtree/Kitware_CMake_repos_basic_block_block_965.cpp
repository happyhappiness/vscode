{
  if (!lib) {
    return 0;
  }
  return !shl_unload(lib);
}