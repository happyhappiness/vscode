static int match_file_name(char *fname,STRUCT_STAT *st)
{
  if (check_exclude(fname,local_exclude_list,st)) {
    if (verbose > 2)
      rprintf(FINFO,"excluding file %s\n",fname);
    return 0;
  }
  return 1;
}