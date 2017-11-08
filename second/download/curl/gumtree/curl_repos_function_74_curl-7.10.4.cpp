static int formparse(char *input,
                     struct curl_httppost **httppost,
                     struct curl_httppost **last_post)
{
  /* nextarg MUST be a string in the format 'name=contents' and we'll
     build a linked list with the info */
  char name[256];
  char *contents;
  char major[128];
  char minor[128];
  char *contp;
  const char *type = NULL;
  char *sep;
  char *sep2;

  /* Preallocate contents to the length of input to make sure we don't
     overwrite anything. */
  contents = malloc(strlen(input));
  contents[0] = '\000';
 
  if(1 <= sscanf(input, "%255[^=]=%[^\n]", name, contents)) {
    /* the input was using the correct format */
    contp = contents;

    if('@' == contp[0]) {
      struct multi_files *multi_start = NULL, *multi_current = NULL;
      /* we use the @-letter to indicate file name(s) */
      contp++;

      multi_start = multi_current=NULL;

      do {
	/* since this was a file, it may have a content-type specifier
	   at the end too, or a filename. Or both. */
        char *ptr;
        char *filename=NULL;

	sep=strchr(contp, FORM_TYPE_SEPARATOR);
	sep2=strchr(contp, FORM_FILE_SEPARATOR);

	/* pick the closest */
	if(sep2 && (sep2 < sep)) {
	  sep = sep2;

	  /* no type was specified! */
	}

        type = NULL;

	if(sep) {

	  /* if we got here on a comma, don't do much */
	  if(FORM_FILE_SEPARATOR == *sep)
	    ptr = NULL;
	  else
            ptr = sep+1;

	  *sep=0; /* terminate file name at separator */

	  while(ptr && (FORM_FILE_SEPARATOR!= *ptr)) {

            /* pass all white spaces */
            while(isspace((int)*ptr))
              ptr++;

            if(curl_strnequal("type=", ptr, 5)) {

              /* set type pointer */
              type = &ptr[5];
	    
              /* verify that this is a fine type specifier */
              if(2 != sscanf(type, "%127[^/]/%127[^;,\n]",
                             major, minor)) {
                fprintf(stderr, "Illegally formatted content-type field!\n");
                free(contents);
                FreeMultiInfo (multi_start);
                return 2; /* illegal content-type syntax! */
              }
              /* now point beyond the content-type specifier */
              sep = (char *)type + strlen(major)+strlen(minor)+1;

              *sep=0; /* zero terminate type string */

              ptr=sep+1;
            }
            else if(curl_strnequal("filename=", ptr, 9)) {
              filename = &ptr[9];
              ptr=strchr(filename, FORM_TYPE_SEPARATOR);
              if(!ptr) {
                ptr=strchr(filename, FORM_FILE_SEPARATOR);
              }
              if(ptr) {
                *ptr=0; /* zero terminate */
                ptr++;
              }
            }
            else
              /* confusion, bail out of loop */
              break;
	  }
          /* find the following comma */
          if(ptr)
            sep=strchr(ptr, FORM_FILE_SEPARATOR);
          else
            sep=NULL;
	}
	else {
	  sep=strchr(contp, FORM_FILE_SEPARATOR);
	}
	if(sep) {
	  /* the next file name starts here */
	  *sep =0;
	  sep++;
	}
        /* if type == NULL curl_formadd takes care of the problem */

        if (!AddMultiFiles (contp, type, filename, &multi_start,
                            &multi_current)) {
          fprintf(stderr, "Error building form post!\n");
          free(contents);
          FreeMultiInfo (multi_start);
          return 3;
        }
	contp = sep; /* move the contents pointer to after the separator */

      } while(sep && *sep); /* loop if there's another file name */

      /* now we add the multiple files section */
      if (multi_start) {
        struct curl_forms *forms = NULL;
        struct multi_files *ptr = multi_start;
        unsigned int i, count = 0;
        while (ptr) {
          ptr = ptr->next;
          ++count;
        }
        forms =
          (struct curl_forms *)malloc((count+1)*sizeof(struct curl_forms));
        if (!forms)
        {
          fprintf(stderr, "Error building form post!\n");
          free(contents);
          FreeMultiInfo (multi_start);
          return 4;
        }
        for (i = 0, ptr = multi_start; i < count; ++i, ptr = ptr->next)
        {
          forms[i].option = ptr->form.option;
          forms[i].value = ptr->form.value;
        }
        forms[count].option = CURLFORM_END;
        FreeMultiInfo (multi_start);
        if (curl_formadd (httppost, last_post,
                          CURLFORM_COPYNAME, name,
                          CURLFORM_ARRAY, forms, CURLFORM_END) != 0) {
          fprintf(stderr, "curl_formadd failed!\n");
          free(forms);
          free(contents);
          return 5;
        }
        free(forms);
      }
    }
    else {
      if( contp[0]=='<' ) {
        if (curl_formadd (httppost, last_post,
                          CURLFORM_COPYNAME, name,
                          CURLFORM_FILECONTENT, contp+1, CURLFORM_END) != 0) {
          fprintf(stderr, "curl_formadd failed!\n");
          free(contents);
          return 6;
        }
      }
      else {
        if (curl_formadd (httppost, last_post,
                          CURLFORM_COPYNAME, name,
                          CURLFORM_COPYCONTENTS, contp, CURLFORM_END) != 0) {
          fprintf(stderr, "curl_formadd failed!\n");
          free(contents);
          return 7;
        }
      }
    }

  }
  else {
    fprintf(stderr, "Illegally formatted input field!\n");
    free(contents);
    return 1;
  }
  free(contents);
  return 0;
}