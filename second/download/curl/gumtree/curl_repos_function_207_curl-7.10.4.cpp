CURLcode Curl_getFormData(struct FormData **finalform,
                          struct curl_httppost *post,
                          int *sizep)
{
  struct FormData *form = NULL;
  struct FormData *firstform;
  struct curl_httppost *file;
  CURLcode result = CURLE_OK;

  int size =0;
  char *boundary;
  char *fileboundary=NULL;
  struct curl_slist* curList;

  *finalform=NULL; /* default form is empty */

  if(!post)
    return result; /* no input => no output! */

  boundary = Curl_FormBoundary();
  
  /* Make the first line of the output */
  AddFormDataf(&form,
               "Content-Type: multipart/form-data;"
               " boundary=%s\r\n",
               boundary);
  /* we DO NOT count that line since that'll be part of the header! */

  firstform = form;
  
  do {

    if(size)
      size += AddFormDataf(&form, "\r\n");

    /* boundary */
    size += AddFormDataf(&form, "--%s\r\n", boundary);

    size += AddFormData(&form,
                        "Content-Disposition: form-data; name=\"", 0);

    size += AddFormData(&form, post->name, post->namelength);

    size += AddFormData(&form, "\"", 0);

    if(post->more) {
      /* If used, this is a link to more file names, we must then do
         the magic to include several files with the same field name */

      fileboundary = Curl_FormBoundary();

      size += AddFormDataf(&form,
                           "\r\nContent-Type: multipart/mixed,"
                           " boundary=%s\r\n",
                           fileboundary);
    }

    file = post;

    do {

      /* If 'showfilename' is set, that is a faked name passed on to us
         to use to in the formpost. If that is not set, the actually used
         local file name should be added. */

      if(post->more) {
        /* if multiple-file */
        size += AddFormDataf(&form,
                             "\r\n--%s\r\nContent-Disposition: "
                             "attachment; filename=\"%s\"",
                             fileboundary,
                             (file->showfilename?file->showfilename:
                              file->contents));
      }
      else if((post->flags & HTTPPOST_FILENAME) ||

              /* CMC: Added support for buffer uploads */
              (post->flags & HTTPPOST_BUFFER)) {

        size += AddFormDataf(&form,
                             "; filename=\"%s\"",
                             (post->showfilename?post->showfilename:
                              post->contents));
      }
      
      if(file->contenttype) {
        /* we have a specified type */
        size += AddFormDataf(&form,
                             "\r\nContent-Type: %s",
                             file->contenttype);
      }

      curList = file->contentheader;
      while( curList ) {
        /* Process the additional headers specified for this form */
        size += AddFormDataf( &form, "\r\n%s", curList->data );
        curList = curList->next;
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

      size += AddFormData(&form, "\r\n\r\n", 0);

      if((post->flags & HTTPPOST_FILENAME) ||
         (post->flags & HTTPPOST_READFILE)) {
        /* we should include the contents from the specified file */
        FILE *fileread;
        char buffer[1024];
        int nread;

        fileread = strequal("-", file->contents)?stdin:
          /* binary read for win32 crap */
          /*VMS??*/ fopen(file->contents, "rb");  /* ONLY ALLOWS FOR STREAM FILES ON VMS */
        /*VMS?? Stream files are OK, as are FIXED & VAR files WITHOUT implied CC */
        /*VMS?? For implied CC, every record needs to have a \n appended & 1 added to SIZE */
        if(fileread) {
          while((nread = fread(buffer, 1, 1024, fileread)))
            size += AddFormData(&form, buffer, nread);

          if(fileread != stdin)
            fclose(fileread);
        }
        else {
#if 0
          /* File wasn't found, add a nothing field! */
          size += AddFormData(&form, "", 0);
#endif
          Curl_formclean(firstform);
          free(boundary);
          *finalform = NULL;
          return CURLE_READ_ERROR;
        }

        /* CMC: Added support for buffer uploads */
      } else if (post->flags & HTTPPOST_BUFFER) {
          /* include contents of buffer */
          size += AddFormData(&form, post->buffer, post->bufferlength);
      }

      else {
        /* include the contents we got */
        size += AddFormData(&form, post->contents, post->contentslength);
      }
    } while((file = file->more)); /* for each specified file for this field */

    if(post->more) {
      /* this was a multiple-file inclusion, make a termination file
         boundary: */
      size += AddFormDataf(&form,
                           "\r\n--%s--",
                           fileboundary);     
      free(fileboundary);
    }

  } while((post=post->next)); /* for each field */

  /* end-boundary for everything */
  size += AddFormDataf(&form,
                       "\r\n--%s--\r\n",
                       boundary);

  *sizep = size;

  free(boundary);

  *finalform=firstform;

  return result;
}