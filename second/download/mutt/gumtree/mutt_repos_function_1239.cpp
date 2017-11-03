BODY *mutt_make_file_attach (const char *path)
{
  BODY *att;
  CONTENT *info;

  att = mutt_new_body ();
  att->filename = safe_strdup (path);

  /* Attempt to determine the appropriate content-type based on the filename
   * suffix.
   */

#if 0

  if ((n = mutt_lookup_mime_type (buf, sizeof (buf), xbuf, sizeof (xbuf), path)) != TYPEOTHER
      || *xbuf != '\0')
  {
    att->type = n;
    att->subtype = safe_strdup (buf);
    att->xtype = safe_strdup (xbuf);
  }

#else

  mutt_lookup_mime_type (att, path);

#endif

  if ((info = mutt_get_content_info (path, att)) == NULL)
  {
    mutt_free_body (&att);
    return NULL;
  }

  if (!att->subtype)
  {
    if (info->lobin == 0 || (info->lobin + info->hibin + info->ascii)/ info->lobin >= 10)
    {
      /*
       * Statistically speaking, there should be more than 10% "lobin"
       * chars if this is really a binary file...
       */
      att->type = TYPETEXT;
      att->subtype = safe_strdup ("plain");
    }
    else
    {
      att->type = TYPEAPPLICATION;
      att->subtype = safe_strdup ("octet-stream");
    }
  }

  FREE(&info);
  mutt_update_encoding (att);
  return (att);
}