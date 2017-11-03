int check_exclude(char *name,char **local_exclude_list)
{
  int n;

  if (exclude_list) {
    for (n=0; exclude_list[n]; n++)
      if (check_one_exclude(name,exclude_list[n]))
	return 1;
  }

  if (local_exclude_list) {
    for (n=0; local_exclude_list[n]; n++)
      if (check_one_exclude(name,local_exclude_list[n]))
	return 1;      
  }

  return 0;
}