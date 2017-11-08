static void server_options(char **args,int *argc)
{
  int ac = *argc;
  static char argstr[50];
  static char bsize[30];
  int i, x;

  args[ac++] = "--server";

  if (!sender)
    args[ac++] = "--sender";

  x = 1;
  argstr[0] = '-';
  for (i=0;i<verbose;i++)
    argstr[x++] = 'v';
  if (make_backups)
    argstr[x++] = 'b';
  if (update_only)
    argstr[x++] = 'u';
  if (dry_run)
    argstr[x++] = 'n';
  if (preserve_links)
    argstr[x++] = 'l';
  if (copy_links)
    argstr[x++] = 'L';
  if (whole_file)
    argstr[x++] = 'W';
  if (preserve_hard_links)
    argstr[x++] = 'H';
  if (preserve_uid)
    argstr[x++] = 'o';
  if (preserve_gid)
    argstr[x++] = 'g';
  if (preserve_devices)
    argstr[x++] = 'D';
  if (preserve_times)
    argstr[x++] = 't';
  if (preserve_perms)
    argstr[x++] = 'p';
  if (recurse)
    argstr[x++] = 'r';
  if (always_checksum)
    argstr[x++] = 'c';
  if (cvs_exclude)
    argstr[x++] = 'C';
  if (ignore_times)
    argstr[x++] = 'I';
  if (relative_paths)
    argstr[x++] = 'R';
  if (one_file_system)
    argstr[x++] = 'x';
  if (sparse_files)
    argstr[x++] = 'S';
  if (do_compression)
    argstr[x++] = 'z';
  argstr[x] = 0;

  if (x != 1) args[ac++] = argstr;

  if (block_size != BLOCK_SIZE) {
    sprintf(bsize,"-B%d",block_size);
    args[ac++] = bsize;
  }    

  if (strcmp(backup_suffix, BACKUP_SUFFIX)) {
	  args[ac++] = "--suffix";
	  args[ac++] = backup_suffix;
  }

  if (delete_mode)
    args[ac++] = "--delete";

  if (numeric_ids)
    args[ac++] = "--numeric-ids";

  if (tmpdir) {
	  args[ac++] = "--temp-dir";
	  args[ac++] = tmpdir;
  }

  *argc = ac;
}