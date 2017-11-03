static gpgme_data_t file_to_data_object (FILE *fp, long offset, long length)
{
  int err = 0;
  gpgme_data_t data;
  
  err = gpgme_data_new_from_filepart (&data, NULL, fp, offset, length);
  if (err) 
    {
      mutt_error (_("error allocating data object: %s\n"), gpgme_strerror (err));
      return NULL;
    }

  return data;
}