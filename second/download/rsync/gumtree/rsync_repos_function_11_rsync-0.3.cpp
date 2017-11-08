void add_exclude_file(char *fname)
{
  exclude_list = make_exclude_list(fname,exclude_list);
}