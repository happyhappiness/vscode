static int
handle_option(int letter, int options)
{
switch(letter)
  {
  case -1:  help(); exit(0);
  case 'c': count_only = TRUE; break;
  case 'h': filenames = FALSE; break;
  case 'i': options |= PCRE_CASELESS; break;
  case 'l': filenames_only = TRUE;
  case 'n': number = TRUE; break;
  case 'r': recurse = TRUE; break;
  case 's': silent = TRUE; break;
  case 'v': invert = TRUE; break;
  case 'x': whole_lines = TRUE; options |= PCRE_ANCHORED; break;

  case 'V':
  fprintf(stderr, "pcregrep version %s using ", VERSION);
  fprintf(stderr, "PCRE version %s\n", pcre_version());
  exit(0);
  break;

  default:
  fprintf(stderr, "pcregrep: Unknown option -%c\n", letter);
  exit(usage(2));
  }

return options;
}