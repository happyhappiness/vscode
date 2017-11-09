static CURLcode libcurl_generate_mime(curl_mime *mime, int *mimeno)
{
  CURLcode ret = CURLE_OK;
  int i;
  curl_off_t size;
  curl_mimepart *part;
  char *filename;
  char *escaped = NULL;
  char *cp;
  char *data;

  /* May need several mime variables, so invent name */
  *mimeno = ++easysrc_mime_count;

  DECL1("curl_mime *mime%d;", *mimeno);
  DATA1("mime%d = NULL;", *mimeno);
  CODE1("mime%d = curl_mime_init(hnd);", *mimeno);
  CLEAN1("curl_mime_free(mime%d);", *mimeno);
  CLEAN1("mime%d = NULL;", *mimeno);
  if(mime->firstpart) {
    DECL1("curl_mimepart *part%d;", *mimeno);
    for(part = mime->firstpart; part; part = part->nextpart) {
      CODE2("part%d = curl_mime_addpart(mime%d);", *mimeno, *mimeno);
      filename = part->filename;
      switch(part->kind) {
      case MIMEKIND_FILE:
        Curl_safefree(escaped);
        escaped = c_escape(part->data, CURL_ZERO_TERMINATED);
        if(!escaped)
          return CURLE_OUT_OF_MEMORY;
        CODE2("curl_mime_filedata(part%d, \"%s\");", *mimeno, escaped);
        if(!filename)
          CODE1("curl_mime_filename(part%d, NULL);", *mimeno);
        else {
          /* Fast check to see if remote file name is base name. */
          filename = part->data;
          for(cp = filename; *cp; cp++)
            if(*cp == '/' || *cp == '\\')
              filename = cp + 1;
          if(!part->filename || !strcmp(filename, part->filename))
            filename = NULL;
          else
            filename = part->filename;
        }
        break;
      case MIMEKIND_CALLBACK:
        /* Can only be reading stdin in the current context. */
        CODE1("curl_mime_data_cb(part%d, -1, (curl_read_callback) fread, \\",
              *mimeno);
        CODE0("                  (curl_seek_callback) fseek, NULL, stdin);");
        break;
      case MIMEKIND_DATA:
#ifdef CURL_DOES_CONVERSIONS
          /* Data is stored in ASCII and we want in in the host character
             code. Convert it back for output. */
          data = malloc(part->datasize + 1);
          if(!data) {
            ret = CURLE_OUT_OF_MEMORY;
            goto nomem;
          }
          memcpy(data, part->data, part->datasize + 1);
          ret = convert_from_network(data, strlen(data));
          if(ret) {
            Curl_safefree(data);
            goto nomem;
          }
#else
        data = part->data;
#endif

        /* Are there any nul byte in data? */
        for(cp = data; *cp; cp++)
          ;
        size = (cp == data + part->datasize)? (curl_off_t) -1: part->datasize;
        Curl_safefree(escaped);
        escaped = c_escape(data, (size_t) part->datasize);
#ifdef CURL_DOES_CONVERSIONS
        Curl_safefree(data);
#endif
        if(!escaped)
          return CURLE_OUT_OF_MEMORY;
        if(size >= 0)
          CODE3("curl_mime_data(part%d, \"%s\", %" CURL_FORMAT_CURL_OFF_T ");",
                                *mimeno, escaped, size);
        else
          CODE2("curl_mime_data(part%d, \"%s\", CURL_ZERO_TERMINATED);",
                                *mimeno, escaped);
        break;
      case MIMEKIND_MULTIPART:
        ret = libcurl_generate_mime(part->arg, &i);
        if(ret)
          goto nomem;
        CODE2("curl_mime_subparts(part%d, mime%d);", *mimeno, i);
        CODE1("mime%d = NULL;", i);   /* Avoid freeing in CLEAN sequence. */
        break;
      default:
        /* Other cases not possible in this context. */
        break;
      }

      if(part->encoder) {
        Curl_safefree(escaped);
        escaped = c_escape(part->encoder->name, CURL_ZERO_TERMINATED);
        if(!escaped)
          return CURLE_OUT_OF_MEMORY;
        CODE2("curl_mime_encoder(part%d, \"%s\");", *mimeno, escaped);
      }

      if(filename) {
        Curl_safefree(escaped);
        escaped = c_escape(filename, CURL_ZERO_TERMINATED);
        if(!escaped)
          return CURLE_OUT_OF_MEMORY;
        CODE2("curl_mime_filename(part%d, \"%s\");", *mimeno, escaped);
      }

      if(part->name) {
        Curl_safefree(escaped);
        escaped = c_escape(part->name, CURL_ZERO_TERMINATED);
        if(!escaped)
          return CURLE_OUT_OF_MEMORY;
        CODE2("curl_mime_name(part%d, \"%s\");", *mimeno, escaped);
      }

      if(part->mimetype) {
        Curl_safefree(escaped);
        escaped = c_escape(part->mimetype, CURL_ZERO_TERMINATED);
        if(!escaped)
          return CURLE_OUT_OF_MEMORY;
        CODE2("curl_mime_type(part%d, \"%s\");", *mimeno, escaped);
      }

      if(part->userheaders) {
        int ownership = part->flags & MIME_USERHEADERS_OWNER? 1: 0;

        ret = libcurl_generate_slist(part->userheaders, &i);
        if(ret)
          goto nomem;
        CODE3("curl_mime_headers(part%d, slist%d, %d);",
              *mimeno, i, ownership);
        if(ownership)
          CODE1("slist%d = NULL;", i); /* Prevent freeing in CLEAN sequence. */
      }
    }
  }

nomem:
  Curl_safefree(escaped);
  return ret;
}