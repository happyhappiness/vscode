CURLcode Curl_getFormData(struct FormData **finalform,
                          struct curl_httppost *post,
                          curl_off_t *sizep)
{
  struct FormData *form = NULL;
  struct FormData *firstform;
  struct curl_httppost *file;
  CURLcode result = CURLE_OK;

  curl_off_t size=0; /* support potentially ENORMOUS formposts */
  char *boundary;
  char *fileboundary=NULL;
  struct curl_slist* curList;

  *finalform=NULL; /* default form is empty */

  if(!post)
    return result; /* no input => no output! */

  boundary = Curl_FormBoundary();
  if(!boundary)
    return CURLE_OUT_OF_MEMORY;

  /* Make the first line of the output */
  result = AddFormDataf(&form, NULL,
                        "Content-Type: multipart/form-data;"
                        " boundary=%s\r\n",
                        boundary);
  if (result) {
    free(boundary);
    return result;
  }
  /* we DO NOT include that line in the total size of the POST, since it'll be
     part of the header! */

  firstform = form;

  do {

    if(size) {
      result = AddFormDataf(&form, &size, "\r\n");
      if (result)
        break;
    }

    /* boundary */
    result = AddFormDataf(&form, &size, "--%s\r\n", boundary);
    if (result)
      break;

    result = AddFormDataf(&form, &size,
                          "Content-Disposition: form-data; name=\"");
    if (result)
      break;

    result = AddFormData(&form, FORM_DATA, post->name, post->namelength,
                         &size);
    if (result)
      break;

    result = AddFormDataf(&form, &size, "\"");
    if (result)
      break;

    if(post->more) {
      /* If used, this is a link to more file names, we must then do
         the magic to include several files with the same field name */

      fileboundary = Curl_FormBoundary();

      result = AddFormDataf(&form, &size,
                            "\r\nContent-Type: multipart/mixed,"
                            " boundary=%s\r\n",
                            fileboundary);
      if (result)
        break;
    }

    file = post;

    do {

      /* If 'showfilename' is set, that is a faked name passed on to us
         to use to in the formpost. If that is not set, the actually used
         local file name should be added. */

      if(post->more) {
        /* if multiple-file */
        char *filebasename=
          (!file->showfilename)?strippath(file->contents):NULL;

        result = AddFormDataf(&form, &size,
                              "\r\n--%s\r\nContent-Disposition: "
                              "attachment; filename=\"%s\"",
                              fileboundary,
                              (file->showfilename?file->showfilename:
                               filebasename));
        if (filebasename)
          free(filebasename);
        if (result)
          break;
      }
      else if((post->flags & HTTPPOST_FILENAME) ||
              (post->flags & HTTPPOST_BUFFER)) {

        char *filebasename=
          (!post->showfilename)?strippath(post->contents):NULL;

        result = AddFormDataf(&form, &size,
                              "; filename=\"%s\"",
                              (post->showfilename?post->showfilename:
                               filebasename));
        if (filebasename)
          free(filebasename);

        if (result)
          break;
      }

      if(file->contenttype) {
        /* we have a specified type */
        result = AddFormDataf(&form, &size,
                              "\r\nContent-Type: %s",
                              file->contenttype);
        if (result)
          break;
      }

      curList = file->contentheader;
      while( curList ) {
        /* Process the additional headers specified for this form */
        result = AddFormDataf( &form, &size, "\r\n%s", curList->data );
        if (result)
          break;
        curList = curList->next;
      }
      if (result) {
        Curl_formclean(firstform);
        free(boundary);
        return result;
      }

#if 0
      /* The header Content-Transfer-Encoding: seems to confuse some receivers
       * (like the built-in PHP engine). While I can't see any reason why it
       * should, I can just as well skip this to the benefit of the users who
       * are using such confused receivers.
       */

      if(file->contenttype &&
         !checkprefix("text/", file->contenttype)) {
        /* this is not a text content, mention our binary encoding */
        size += AddFormData(&form, "\r\nContent-Transfer-Encoding: binary", 0);
      }
#endif

      result = AddFormDataf(&form, &size, "\r\n\r\n");
      if (result)
        break;

      if((post->flags & HTTPPOST_FILENAME) ||
         (post->flags & HTTPPOST_READFILE)) {
        /* we should include the contents from the specified file */
        FILE *fileread;

        fileread = strequal("-", file->contents)?
          stdin:fopen(file->contents, "rb"); /* binary read for win32  */

        /*
         * VMS: This only allows for stream files on VMS.  Stream files are
         * OK, as are FIXED & VAR files WITHOUT implied CC For implied CC,
         * every record needs to have a \n appended & 1 added to SIZE
         */

        if(fileread) {
          if(fileread != stdin) {
            /* close the file again */
            fclose(fileread);
            /* add the file name only - for later reading from this */
            result = AddFormData(&form, FORM_FILE, file->contents, 0, &size);
          }
          else {
            /* When uploading from stdin, we can't know the size of the file,
             * thus must read the full file as before. We *could* use chunked
             * transfer-encoding, but that only works for HTTP 1.1 and we
             * can't be sure we work with such a server.
             */
            size_t nread;
            char buffer[512];
            while((nread = fread(buffer, 1, sizeof(buffer), fileread))) {
              result = AddFormData(&form, FORM_DATA, buffer, nread, &size);
              if (result)
                break;
            }
          }

          if (result) {
            Curl_formclean(firstform);
            free(boundary);
            return result;
          }

        }
        else {
          Curl_formclean(firstform);
          free(boundary);
          *finalform = NULL;
          return CURLE_READ_ERROR;
        }

      }
      else if (post->flags & HTTPPOST_BUFFER) {
        /* include contents of buffer */
        result = AddFormData(&form, FORM_DATA, post->buffer,
                             post->bufferlength, &size);
          if (result)
            break;
      }

      else {
        /* include the contents we got */
        result = AddFormData(&form, FORM_DATA, post->contents,
                             post->contentslength, &size);
        if (result)
          break;
      }
    } while((file = file->more)); /* for each specified file for this field */
    if (result) {
      Curl_formclean(firstform);
      free(boundary);
      return result;
    }

    if(post->more) {
      /* this was a multiple-file inclusion, make a termination file
         boundary: */
      result = AddFormDataf(&form, &size,
                           "\r\n--%s--",
                           fileboundary);
      free(fileboundary);
      if (result)
        break;
    }

  } while((post=post->next)); /* for each field */
  if (result) {
    Curl_formclean(firstform);
    free(boundary);
    return result;
  }

  /* end-boundary for everything */
  result = AddFormDataf(&form, &size,
                       "\r\n--%s--\r\n",
                       boundary);
  if (result) {
    Curl_formclean(firstform);
    free(boundary);
    return result;
  }

  *sizep = size;

  free(boundary);

  *finalform=firstform;

  return result;
}