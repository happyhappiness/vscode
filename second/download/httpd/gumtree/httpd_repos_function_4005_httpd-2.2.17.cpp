int
main(int argc, char **argv)
{
int i, j;
int rc = 1;
int options = 0;
int errptr;
const char *error;
BOOL only_one_at_top;

/* Process the options */

for (i = 1; i < argc; i++)
  {
  if (argv[i][0] != '-') break;

  /* Missing options */

  if (argv[i][1] == 0) exit(usage(2));

  /* Long name options */

  if (argv[i][1] == '-')
    {
    option_item *op;

    if (strncmp(argv[i]+2, "file=", 5) == 0)
      {
      pattern_filename = argv[i] + 7;
      continue;
      }

    for (op = optionlist; op->one_char != 0; op++)
      {
      if (strcmp(argv[i]+2, op->long_name) == 0)
        {
        options = handle_option(op->one_char, options);
        break;
        }
      }
    if (op->one_char == 0)
      {
      fprintf(stderr, "pcregrep: Unknown option %s\n", argv[i]);
      exit(usage(2));
      }
    }

  /* One-char options */

  else
    {
    char *s = argv[i] + 1;
    while (*s != 0)
      {
      if (*s == 'f')
        {
        pattern_filename = s + 1;
        if (pattern_filename[0] == 0)
          {
          if (i >= argc - 1)
            {
            fprintf(stderr, "pcregrep: File name missing after -f\n");
            exit(usage(2));
            }
          pattern_filename = argv[++i];
          }
        break;
        }
      else options = handle_option(*s++, options);
      }
    }
  }

pattern_list = (pcre **)malloc(MAX_PATTERN_COUNT * sizeof(pcre *));
hints_list = (pcre_extra **)malloc(MAX_PATTERN_COUNT * sizeof(pcre_extra *));

if (pattern_list == NULL || hints_list == NULL)
  {
  fprintf(stderr, "pcregrep: malloc failed\n");
  return 2;
  }

/* Compile the regular expression(s). */

if (pattern_filename != NULL)
  {
  FILE *f = fopen(pattern_filename, "r");
  char buffer[BUFSIZ];
  if (f == NULL)
    {
    fprintf(stderr, "pcregrep: Failed to open %s: %s\n", pattern_filename,
      strerror(errno));
    return 2;
    }
  while (fgets(buffer, sizeof(buffer), f) != NULL)
    {
    char *s = buffer + (int)strlen(buffer);
    if (pattern_count >= MAX_PATTERN_COUNT)
      {
      fprintf(stderr, "pcregrep: Too many patterns in file (max %d)\n",
        MAX_PATTERN_COUNT);
      return 2;
      }
    while (s > buffer && isspace((unsigned char)(s[-1]))) s--;
    if (s == buffer) continue;
    *s = 0;
    pattern_list[pattern_count] = pcre_compile(buffer, options, &error,
      &errptr, NULL);
    if (pattern_list[pattern_count++] == NULL)
      {
      fprintf(stderr, "pcregrep: Error in regex number %d at offset %d: %s\n",
        pattern_count, errptr, error);
      return 2;
      }
    }
  fclose(f);
  }

/* If no file name, a single regex must be given inline */

else
  {
  if (i >= argc) return usage(2);
  pattern_list[0] = pcre_compile(argv[i++], options, &error, &errptr, NULL);
  if (pattern_list[0] == NULL)
    {
    fprintf(stderr, "pcregrep: Error in regex at offset %d: %s\n", errptr,
      error);
    return 2;
    }
  pattern_count++;
  }

/* Study the regular expressions, as we will be running them may times */

for (j = 0; j < pattern_count; j++)
  {
  hints_list[j] = pcre_study(pattern_list[j], 0, &error);
  if (error != NULL)
    {
    char s[16];
    if (pattern_count == 1) s[0] = 0; else sprintf(s, " number %d", j);
    fprintf(stderr, "pcregrep: Error while studying regex%s: %s\n", s, error);
    return 2;
    }
  }

/* If there are no further arguments, do the business on stdin and exit */

if (i >= argc) return pcregrep(stdin, NULL);

/* Otherwise, work through the remaining arguments as files or directories.
Pass in the fact that there is only one argument at top level - this suppresses
the file name if the argument is not a directory. */

only_one_at_top = (i == argc - 1);
if (filenames_only) filenames = TRUE;

for (; i < argc; i++)
  {
  int frc = grep_or_recurse(argv[i], recurse, filenames, only_one_at_top);
  if (frc == 0 && rc == 1) rc = 0;
  }

return rc;
}