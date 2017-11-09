BODY *mutt_make_file_attach (const char *path)
{
  BODY *att;
  CONTENT *info;

  att = mutt_new_body ();
  att->filename = safe_strdup (path);

  if (MimeTypeQueryCmd && *MimeTypeQueryCmd &&
      option (OPTMIMETYPEQUERYFIRST))
    run_mime_type_query (att);

  /* Attempt to determine the appropriate content-type based on the filename
   * suffix.
   */
  if (!att->subtype)
    mutt_lookup_mime_type (att, path);

  if (!att->subtype &&
      MimeTypeQueryCmd && *MimeTypeQueryCmd &&
      !option (OPTMIMETYPEQUERYFIRST))
    run_mime_type_query (att);

  if ((info = mutt_get_content_info (path, att)) == NULL)
  {
    mutt_free_body (&att);
    return NULL;
  }

  if (!att->subtype)
  {
    if ((info->nulbin == 0) &&
        (info->lobin == 0 || (info->lobin + info->hibin + info->ascii)/ info->lobin >= 10))
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