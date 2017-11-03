static int check_one_exclude(char *name,char *pattern)
{
  char *p;

  if (!strchr(pattern,'/') && (p=strrchr(name,'/')))
    name = p+1;

  if (!name[0]) return 0;

  if (is_regex(pattern)) {
    if (fnmatch(pattern, name, 0) == 0)
      return 1;
  } else {
    int l1 = strlen(name);
    int l2 = strlen(pattern);
    if (l2 <= l1 && 
	strcmp(name+(l1-l2),pattern) == 0 &&
	(l1==l2 || name[l1-(l2+1)] == '/'))
      return 1;
  }

  return 0;
}