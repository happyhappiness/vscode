static int match_file_name(char *fname,struct stat *st)
{
  if (check_exclude(fname,local_exclude_list)) {
    if (verbose > 2)
      fprintf(FERROR,"excluding file %s\n",fname);
    return 0;
  }
  return 1;
}