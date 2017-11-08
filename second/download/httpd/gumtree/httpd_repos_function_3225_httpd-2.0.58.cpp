static void
help(void)
{
option_item *op;

printf("Usage: pcregrep [OPTION]... PATTERN [FILE] ...\n");
printf("Search for PATTERN in each FILE or standard input.\n");
printf("Example: pcregrep -i 'hello.*world' menu.h main.c\n\n");

printf("Options:\n");

for (op = optionlist; op->one_char != 0; op++)
  {
  int n;
  char s[4];
  if (op->one_char > 0) sprintf(s, "-%c,", op->one_char); else strcpy(s, "   ");
  printf("  %s --%s%n", s, op->long_name, &n);
  n = 30 - n;
  if (n < 1) n = 1;
  printf("%.*s%s\n", n, "                    ", op->help_text);
  }

printf("\n  -f<filename>  or  --file=<filename>\n");
printf("    Read patterns from <filename> instead of using a command line option.\n");
printf("    Trailing white space is removed; blanks lines are ignored.\n");
printf("    There is a maximum of %d patterns.\n", MAX_PATTERN_COUNT);

printf("\nWith no FILE, read standard input. If fewer than two FILEs given, assume -h.\n");
printf("Exit status is 0 if any matches, 1 if no matches, and 2 if trouble.\n");
}