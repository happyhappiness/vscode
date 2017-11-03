const char*
parse_value_nothrow(const char* src, int64_t* value, int base, int unit) {
  if (unit <= 0)
    throw torrent::input_error("Command::string_to_value_unit(...) received unit <= 0.");

  char* last;
  *value = strtoll(src, &last, base);

  if (last == src) {
    if (strcasecmp(src, "no") == 0) { *value = 0; return src + strlen("no"); }
    if (strcasecmp(src, "yes") == 0) { *value = 1; return src + strlen("yes"); }
    if (strcasecmp(src, "true") == 0) { *value = 1; return src + strlen("true"); }
    if (strcasecmp(src, "false") == 0) { *value = 0; return src + strlen("false"); }

    return src;
  }

  switch (*last) {
  case 'b':
  case 'B': ++last; break;
  case 'k':
  case 'K': *value = *value << 10; ++last; break;
  case 'm':
  case 'M': *value = *value << 20; ++last; break;
  case 'g':
  case 'G': *value = *value << 30; ++last; break;
//   case ' ':
//   case '\0': *value = *value * unit; break;
//   default: throw torrent::input_error("Could not parse value.");
  default: *value = *value * unit; break;
  }

  return last;
}