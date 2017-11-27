static int fc_read_dir (fc_directory_conf_t *dir)
{
  int status;

  dir->files_num = 0;
  dir->files_size = 0;

  if (dir->mtime != 0)
    dir->now = time (NULL);
    
  status = walk_directory (dir->path, fc_read_dir_callback, dir,
      /* include hidden */ (dir->options & FC_HIDDEN) ? 1 : 0);
  if (status != 0)
  {
    WARNING ("filecount plugin: walk_directory (%s) failed.", dir->path);
    return (-1);
  }

  fc_submit_dir (dir);

  return (0);
}