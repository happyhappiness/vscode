static char *data_object_to_tempfile (gpgme_data_t data, char *tempf, FILE **ret_fp)
{
  int err;
  char tempfb[_POSIX_PATH_MAX];
  FILE *fp;
  size_t nread = 0;

  if (!tempf)
    {
      mutt_mktemp (tempfb, sizeof (tempfb));
      tempf = tempfb;
    }
  if ((fp = safe_fopen (tempf, tempf == tempfb ? "w+" : "a+")) == NULL)
    {
      mutt_perror _("Can't create temporary file");
      return NULL;
    }

  err = ((gpgme_data_seek (data, 0, SEEK_SET) == -1)
         ? gpgme_error_from_errno (errno) : 0);
  if (!err)
    {
      char buf[4096];

      while ((nread = gpgme_data_read (data, buf, sizeof (buf))))
        {
          if (fwrite (buf, nread, 1, fp) != 1)
            {
              mutt_perror (tempf);
              safe_fclose (&fp);
              unlink (tempf);
              return NULL;
            }
        }
    }
  if (ret_fp)
    rewind (fp);
  else
    safe_fclose (&fp);
  if (nread == -1)
    {
      mutt_error (_("error reading data object: %s\n"), gpgme_strerror (err));
      unlink (tempf);
      safe_fclose (&fp);
      return NULL;
    }
  if (ret_fp)
    *ret_fp = fp;
  return safe_strdup (tempf);
}