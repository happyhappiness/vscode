char*
print_download_title(char* first, char* last, core::Download* d) {
  return print_buffer(first, last, "%s", d->get_download().name().c_str());
}