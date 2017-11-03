static gpgme_data_t create_gpgme_data (void)
{
  gpgme_error_t err;
  gpgme_data_t data;

  err = gpgme_data_new (&data);
  if (err) 
    {
      mutt_error (_("error creating gpgme data object: %s\n"),
                  gpgme_strerror (err));
      sleep (2);
      mutt_exit (1);
    }
  return data;
}