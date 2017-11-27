static int
foreachfile_callback (dirname, data1, data2)
     char *dirname;
     lt_ptr data1;
     lt_ptr data2;
{
  file_worker_func *func = *(file_worker_func **) data1;

  int	  is_done  = 0;
  char   *argz     = 0;
  size_t  argz_len = 0;

  if (list_files_by_dir (dirname, &argz, &argz_len) != 0)
    goto cleanup;
  if (!argz)
    goto cleanup;

  {
    char *filename = 0;
    while ((filename = argz_next (argz, argz_len, filename)))
      if ((is_done = (*func) (filename, data2)))
	break;
  }

 cleanup:
  LT_DLFREE (argz);

  return is_done;
}