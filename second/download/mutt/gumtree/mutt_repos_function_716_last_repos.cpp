static int data_object_to_stream (gpgme_data_t data, FILE *fp)
{
  int err;
  char buf[4096], *p;
  ssize_t nread;

  err = ((gpgme_data_seek (data, 0, SEEK_SET) == -1)
         ? gpgme_error_from_errno (errno) : 0);
  if (err)
    {
      mutt_error (_("error rewinding data object: %s\n"), gpgme_strerror (err));
      return -1;
    }

  while ((nread = gpgme_data_read (data, buf, sizeof (buf))))
    {
      /* fixme: we are not really converting CRLF to LF but just
         skipping CR. Doing it correctly needs a more complex logic */
      for (p=buf; nread; p++, nread--)
        {
          if (*p != '\r')
            putc (*p, fp);
        }

     if (ferror (fp))
       {
         mutt_perror ("[tempfile]");
         return -1;
       }
    }
  if (nread == -1)
    {
      mutt_error (_("error reading data object: %s\n"), strerror (errno));
      return -1;
    }
  return 0;
}