int
main(int argc, char **argv)
{
int i;
int rc = 1;
int options = 0;
int errptr;
const char *error;
BOOL filenames = TRUE;

/* Process the options */

for (i = 1; i < argc; i++)
  {
  char *s;
  if (argv[i][0] != '-') break;
  s = argv[i] + 1;
  while (*s != 0)
    {
    switch (*s++)
      {
      case 'c': count_only = TRUE; break;
      case 'h': filenames = FALSE; break;
      case 'i': options |= PCRE_CASELESS; break;
      case 'l': filenames_only = TRUE;
      case 'n': number = TRUE; break;
      case 's': silent = TRUE; break;
      case 'v': invert = TRUE; break;
      case 'x': whole_lines = TRUE; options |= PCRE_ANCHORED; break;

      case 'V':
      fprintf(stderr, "PCRE version %s\n", pcre_version());
      break;

      default:
      fprintf(stderr, "pgrep: unknown option %c\n", s[-1]);
      return usage(2);
      }
    }
  }

/* There must be at least a regexp argument */

if (i >= argc) return usage(0);

/* Compile the regular expression. */

pattern = pcre_compile(argv[i++], options, &error, &errptr, NULL);
if (pattern == NULL)
  {
  fprintf(stderr, "pgrep: error in regex at offset %d: %s\n", errptr, error);
  return 2;
  }

/* Study the regular expression, as we will be running it may times */

hints = pcre_study(pattern, 0, &error);
if (error != NULL)
  {
  fprintf(stderr, "pgrep: error while studing regex: %s\n", error);
  return 2;
  }

/* If there are no further arguments, do the business on stdin and exit */

if (i >= argc) return pgrep(stdin, NULL);

/* Otherwise, work through the remaining arguments as files. If there is only
one, don't give its name on the output. */

if (i == argc - 1) filenames = FALSE;
if (filenames_only) filenames = TRUE;

for (; i < argc; i++)
  {
  FILE *in = fopen(argv[i], "r");
  if (in == NULL)
    {
    fprintf(stderr, "%s: failed to open: %s\n", argv[i], strerror(errno));
    rc = 2;
    }
  else
    {
    int frc = pgrep(in, filenames? argv[i] : NULL);
    if (frc == 0 && rc == 1) rc = 0;
    fclose(in);
    }
  }

return rc;
}