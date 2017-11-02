int parse_metalink(struct OperationConfig *config, struct OutStruct *outs,
                   const char *metalink_url)
{
  metalink_error_t r;
  metalink_t* metalink;
  metalink_file_t **files;
  bool warnings = FALSE;

  /* metlaink_parse_final deletes outs->metalink_parser */
  r = metalink_parse_final(outs->metalink_parser, NULL, 0, &metalink);
  outs->metalink_parser = NULL;
  if(r != 0) {
    return -1;
  }
  if(metalink->files == NULL) {
    fprintf(config->global->errors, "Metalink: parsing (%s) WARNING "
            "(missing or invalid file name)\n",
            metalink_url);
    metalink_delete(metalink);
    return -1;
  }
  for(files = metalink->files; *files; ++files) {
    struct getout *url;
    /* Skip an entry which has no resource. */
    if(!(*files)->resources) {
      fprintf(config->global->errors, "Metalink: parsing (%s) WARNING "
              "(missing or invalid resource)\n",
              metalink_url, (*files)->name);
      continue;
    }
    if(config->url_get ||
       ((config->url_get = config->url_list) != NULL)) {
      /* there's a node here, if it already is filled-in continue to
         find an "empty" node */
      while(config->url_get && (config->url_get->flags & GETOUT_URL))
        config->url_get = config->url_get->next;
    }

    /* now there might or might not be an available node to fill in! */

    if(config->url_get)
      /* existing node */
      url = config->url_get;
    else
      /* there was no free node, create one! */
      url = new_getout(config);

    if(url) {
      metalinkfile *mlfile;
      mlfile = new_metalinkfile(*files);
      if(!mlfile->checksum) {
        warnings = TRUE;
        fprintf(config->global->errors,
                "Metalink: parsing (%s) WARNING (digest missing)\n",
                metalink_url);
      }
      /* Set name as url */
      GetStr(&url->url, mlfile->filename);

      /* set flag metalink here */
      url->flags |= GETOUT_URL | GETOUT_METALINK;

      if(config->metalinkfile_list) {
        config->metalinkfile_last->next = mlfile;
        config->metalinkfile_last = mlfile;
      }
      else {
        config->metalinkfile_list = config->metalinkfile_last = mlfile;
      }
    }
  }
  metalink_delete(metalink);
  return (warnings) ? -2 : 0;
}