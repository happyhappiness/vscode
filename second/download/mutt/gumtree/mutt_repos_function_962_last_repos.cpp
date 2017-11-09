int mutt_rename_file (char *oldfile, char *newfile)
{
  FILE *ofp, *nfp;

  if (access (oldfile, F_OK) != 0)
    return 1;
  if (access (newfile, F_OK) == 0)
    return 2;
  if ((ofp = fopen (oldfile,"r")) == NULL)
    return 3;
  if ((nfp = safe_fopen (newfile,"w")) == NULL)
  {
    safe_fclose (&ofp);
    return 3;
  }
  mutt_copy_stream (ofp,nfp);
  safe_fclose (&nfp);
  safe_fclose (&ofp);
  mutt_unlink (oldfile);
  return 0;
}