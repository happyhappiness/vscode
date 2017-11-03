static void server_options(char **args,int *argc)
{
  int ac = *argc;
  static char argstr[50];
  static char bsize[30];
  static char slength[30];
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
  if (one_file_system)
    argstr[x++] = 'x';
  argstr[x] = 0;

  if (x != 1) args[ac++] = argstr;

  if (block_size != BLOCK_SIZE) {
    sprintf(bsize,"-B%d",block_size);
    args[ac++] = bsize;
  }    

  if (csum_length != SUM_LENGTH) {
    sprintf(slength,"--csum-length=%d",csum_length);
    args[ac++] = slength;
  }    
  
  if (delete_mode)
    args[ac++] = "--delete";

  *argc = ac;
}