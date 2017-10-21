extern int preserve_uid;
extern int preserve_gid;
extern int preserve_times;

static char **local_exclude_list = NULL;

static void clean_fname(char *name);


/*
  This function is used to check if a file should be included/excluded
  from the list of files based on its name and type etc
 */
static int match_file_name(char *fname,struct stat *st)
{
  if (check_exclude(fname,local_exclude_list)) {
    if (verbose > 2)
      fprintf(stderr,"excluding file %s\n",fname);
    return 0;
  }
  return 1;
}

/* used by the one_file_system code */
static dev_t filesystem_dev;

