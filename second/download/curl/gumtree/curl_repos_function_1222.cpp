CURLcode Curl_getformdata(struct SessionHandle *data,
                          struct FormData **finalform,
                          struct curl_httppost *post,
                          const char *custom_content_type,
                          curl_off_t *sizep)
{
  struct FormData *form = NULL;
  struct FormData *firstform;
  struct curl_httppost *file;
  CURLcode result = CURLE_OK;

  curl_off_t size = 0; /* support potentially ENORMOUS formposts */
  char *boundary;
  char *fileboundary = NULL;
  struct curl_slist* curList;

  *finalform = NULL; /* default form is empty */

  if(!post)
    return result; /* no input => no output! */

  boundary = formboundary(data);
  if(!boundary)
    return CURLE_OUT_OF_MEMORY;

  /* Make the first line of the output */
  result = AddFormDataf(&form, NULL,
                        "%s; boundary=%s\r\n",
                        custom_content_type?custom_content_type:
                        "Content-Type: multipart/form-data",
                        boundary);

  if(result) {
    Curl_safefree(boundary);
    return result;
  }
  /* we DO NOT include that line in the total size of the POST, since it'll be
     part of the header! */

  firstform = form;

  do {

    if(size) {
      result = AddFormDataf(&form, &size, "\r\n");
      if(result)
        break;
    }

    /* boundary */
    result = AddFormDataf(&form, &size, "--%s\r\n", boundary);
    if(result)
      break;

    /* Maybe later this should be disabled when a custom_content_type is
       passed, since Content-Disposition is not meaningful for all multipart
       types.
    */
    result = AddFormDataf(&form, &size,
                          "Content-Disposition: form-data; name=\"");
    if(result)
      break;

    result = AddFormData(&form, FORM_DATA, post->name, post->namelength,
                         &size);
    if(result)
      break;

    result = AddFormDataf(&form, &size, "\"");
    if(result)
      break;

    if(post->more) {
      /* If used, this is a link to more file names, we must then do
         the magic to include several files with the same field name */

      Curl_safefree(fileboundary);
      fileboundary = formboundary(data);
      if(!fileboundary) {
        result = CURLE_OUT_OF_MEMORY;
        break;
      }

      result = AddFormDataf(&form, &size,
                            "\r\nContent-Type: multipart/mixed;"
                            " boundary=%s\r\n",
                            fileboundary);
      if(result)
        break;
    }

    file = post;

    do {

      /* If 'showfilename' is set, that is a faked name passed on to us
         to use to in the formpost. If that is not set, the actually used
         local file name should be added. */

      if(post->more) {
        /* if multiple-file */
        result = AddFormDataf(&form, &size,
                              "\r\n--%s\r\nContent-Disposition: "
                              "attachment",
                              fileboundary);
        if(result)
          break;
        result = formdata_add_filename(file, &form, &size);
        if(result)
          break;
      }
      else if(post->flags & (HTTPPOST_FILENAME|HTTPPOST_BUFFER|
                             HTTPPOST_CALLBACK)) {
        /* it should be noted that for the HTTPPOST_FILENAME and
           HTTPPOST_CALLBACK cases the ->showfilename struct member is always
           assigned at this point */
        if(post->showfilename || (post->flags & HTTPPOST_FILENAME)) {
          result = formdata_add_filename(post, &form, &size);
        }

        if(result)
          break;
      }

      if(file->contenttype) {
        /* we have a specified type */
        result = AddFormDataf(&form, &size,
                              "\r\nContent-Type: %s",
                              file->contenttype);
        if(result)
          break;
      }

      curList = file->contentheader;
      while(curList) {
        /* Process the additional headers specified for this form */
        result = AddFormDataf( &form, &size, "\r\n%s", curList->data );
        if(result)
          break;
        curList = curList->next;
      }
      if(result)
        break;

      result = AddFormDataf(&form, &size, "\r\n\r\n");
      if(result)
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
            /* close the file */
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
            while((nread = fread(buffer, 1, sizeof(buffer), fileread)) != 0) {
              result = AddFormData(&form, FORM_CONTENT, buffer, nread, &size);
              if(result)
                break;
            }
          }
        }
        else {
          if(data)
            failf(data, "couldn't open file \"%s\"", file->contents);
          *finalform = NULL;
          result = CURLE_READ_ERROR;
        }
      }
      else if(post->flags & HTTPPOST_BUFFER)
        /* include contents of buffer */
        result = AddFormData(&form, FORM_CONTENT, post->buffer,
                             post->bufferlength, &size);
      else if(post->flags & HTTPPOST_CALLBACK)
        /* the contents should be read with the callback and the size
           is set with the contentslength */
        result = AddFormData(&form, FORM_CALLBACK, post->userp,
                             post->contentslength, &size);
      else
        /* include the contents we got */
        result = AddFormData(&form, FORM_CONTENT, post->contents,
                             post->contentslength, &size);

      file = file->more;
    } while(file && !result); /* for each specified file for this field */

    if(result)
      break;

    if(post->more) {
      /* this was a multiple-file inclusion, make a termination file
         boundary: */
      result = AddFormDataf(&form, &size,
                           "\r\n--%s--",
                           fileboundary);
      if(result)
        break;
    }

  } while((post = post->next) != NULL); /* for each field */

  /* end-boundary for everything */
  if(!result)
    result = AddFormDataf(&form, &size, "\r\n--%s--\r\n", boundary);

  if(result) {
    Curl_formclean(&firstform);
    Curl_safefree(fileboundary);
    Curl_safefree(boundary);
    return result;
  }

  *sizep = size;

  Curl_safefree(fileboundary);
  Curl_safefree(boundary);

  *finalform = firstform;

  return result;
}