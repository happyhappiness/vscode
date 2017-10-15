char*
print_hhmmss(char* first, char* last, time_t t) {
  return print_buffer(first, last, "%2d:%02d:%02d", (int)t / 3600, ((int)t / 60) % 60, (int)t % 60);
}