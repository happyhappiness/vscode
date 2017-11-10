int
pcre_get_substring_list(const char *subject, int *ovector, int stringcount,
  const char ***listptr)
{
int i;
int size = sizeof(char *);
int double_count = stringcount * 2;
char **stringlist;
char *p;

for (i = 0; i < double_count; i += 2)
  size += sizeof(char *) + ovector[i+1] - ovector[i] + 1;

stringlist = (char **)(pcre_malloc)(size);
if (stringlist == NULL) return PCRE_ERROR_NOMEMORY;

*listptr = (const char **)stringlist;
p = (char *)(stringlist + stringcount + 1);

for (i = 0; i < double_count; i += 2)
  {
  int len = ovector[i+1] - ovector[i];
  memcpy(p, subject + ovector[i], len);
  *stringlist++ = p;
  p += len;
  *p++ = 0;
  }

*stringlist = NULL;
return 0;
}