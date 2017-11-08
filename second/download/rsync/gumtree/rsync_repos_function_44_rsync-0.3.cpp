static int match_file_name(char *fname,struct stat *st)
{
  if (check_exclude(fname,local_exclude_list)) 
    return 0;
  return 1;
}