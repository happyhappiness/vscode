  return print_buffer(first, last, "%2u:%02u:%02u", u->tm_hour, u->tm_min, u->tm_sec);
}

char*
print_ddhhmm(char* first, char* last, time_t t) {
  if (t / (24 * 3600) < 100)
    return print_buffer(first, last, "%2i:%02i:%02i", (int)t / (24 * 3600), ((int)t / 3600) % 24, ((int)t / 60) % 60);
  else
    return print_buffer(first, last, "--:--:--");
}

char*
print_ddmmyyyy(char* first, char* last, time_t t) {
