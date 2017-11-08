struct FormData *Curl_getFormData(struct HttpPost *post,
                                  int *sizep)
{
  struct FormData *form = NULL;
  struct FormData *firstform;

  struct HttpPost *file;

  int size =0;
  char *boundary;
  char *fileboundary=NULL;

  if(!post)
    return NULL; /* no input => no output! */

  boundary = Curl_FormBoundary();
  
  /* Make the first line of the output */
  AddFormDataf(&form,
               "Content-Type: multipart/form-data;"
               " boundary=%s\r\n",
               boundary);
  /* we DO NOT count that line since that'll be part of the header! */

  firstform = form;
  
  do {

    /* boundary */
    size += AddFormDataf(&form, "\r\n--%s\r\n", boundary);

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
      if(post->more) {
	/* if multiple-file */
	size += AddFormDataf(&form,
			     "\r\n--%s\r\nContent-Disposition: attachment; filename=\"%s\"",
			     fileboundary, file->contents);
      }
      else if(post->flags & HTTPPOST_FILENAME) {
	size += AddFormDataf(&form,
			     "; filename=\"%s\"",
			     post->contents);
      }
      
      if(file->contenttype) {
	/* we have a specified type */
	size += AddFormDataf(&form,
			     "\r\nContent-Type: %s",
			     file->contenttype);
      }

#if 0
      /* The header Content-Transfer-Encoding: seems to confuse some receivers
       * (like the built-in PHP engine). While I can't see any reason why it
       * should, I can just as well skip this to the benefit of the users who
       * are using such confused receivers.
       */
      
      if(file->contenttype &&
	 !strnequal("text/", file->contenttype, 5)) {
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
	  while((nread = fread(buffer, 1, 1024, fileread))) {
	    size += AddFormData(&form,
				buffer,
				nread);
	  }
          if(fileread != stdin)
            fclose(fileread);
	} else {
	  size += AddFormData(&form, "[File wasn't found by client]", 0);
	}
      } else {
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

  return firstform;
}