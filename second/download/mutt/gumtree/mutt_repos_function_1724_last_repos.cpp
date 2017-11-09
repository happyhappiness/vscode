int mutt_get_tmp_attachment (BODY *a)
{
  char type[STRING];
  char tempfile[_POSIX_PATH_MAX];
  rfc1524_entry *entry = rfc1524_new_entry();
  FILE *fpin = NULL, *fpout = NULL;
  struct stat st;
  
  if(a->unlink)
    return 0;

  snprintf(type, sizeof(type), "%s/%s", TYPE(a), a->subtype);
  rfc1524_mailcap_lookup(a, type, entry, 0);
  rfc1524_expand_filename(entry->nametemplate, a->filename, 
			  tempfile, sizeof(tempfile));
  
  rfc1524_free_entry(&entry);

  if(stat(a->filename, &st) == -1)
    return -1;

  if((fpin = fopen(a->filename, "r")) && (fpout = safe_fopen(tempfile, "w")))  /* __FOPEN_CHECKED__ */
  {
    mutt_copy_stream (fpin, fpout);
    mutt_str_replace (&a->filename, tempfile);
    a->unlink = 1;

    if(a->stamp >= st.st_mtime)
      mutt_stamp_attachment(a);
  }
  else
    mutt_perror(fpin ? tempfile : a->filename);
  
  if(fpin)  safe_fclose (&fpin);
  if(fpout) safe_fclose (&fpout);
  
  return a->unlink ? 0 : -1;
}