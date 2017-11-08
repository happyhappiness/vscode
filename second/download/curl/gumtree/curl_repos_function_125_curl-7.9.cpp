static
int FormAdd(struct HttpPost **httppost,
            struct HttpPost **last_post,
            va_list params)
{
  FormInfo *first_form_info, *current_form_info, *form_info;
  int return_value = 0;
  const char *prevtype = NULL;
  struct HttpPost *post = NULL;
  CURLformoption next_option;

  first_form_info = (FormInfo *)malloc(sizeof(struct FormInfo));
  if(first_form_info) {
    memset(first_form_info, 0, sizeof(FormInfo));
    current_form_info = first_form_info;
  }
  else
    return 1;

  /** TODO: first check whether char * is not NULL
      TODO: transfer.c
  */
  while ( ((next_option = va_arg(params, CURLformoption)) != CURLFORM_END) &&
          (return_value == 0) )
  {
    switch (next_option)
    {
      case CURLFORM_PTRNAME:
        current_form_info->flags |= HTTPPOST_PTRNAME; /* fall through */
      case CURLFORM_COPYNAME:
        if (current_form_info->name)
          return_value = 2;
        else {
          if (next_option == CURLFORM_PTRNAME)
            current_form_info->name = va_arg(params, char *);
          else {
	    char *name = va_arg(params, char *);
	    if (name)
	      current_form_info->name = name; /* store for the moment */
	    else
	      return_value = 3;
	  }
        }
        break;
      case CURLFORM_NAMELENGTH:
        if (current_form_info->namelength)
          return_value = 2;
        else
          current_form_info->namelength = va_arg(params, long);
        break;
      case CURLFORM_PTRCONTENTS:
        current_form_info->flags |= HTTPPOST_PTRCONTENTS; /* fall through */
      case CURLFORM_COPYCONTENTS:
        if (current_form_info->value)
          return_value = 2;
        else {
          if (next_option == CURLFORM_PTRCONTENTS)
            current_form_info->value = va_arg(params, char *);
          else {
	    char *value = va_arg(params, char *);
	    if (value)
	      current_form_info->value = value; /* store for the moment */
	    else
	      return_value = 3;
	  }
        }
        break;
      case CURLFORM_CONTENTSLENGTH:
        if (current_form_info->contentslength)
          return_value = 2;
        else
          current_form_info->contentslength = va_arg(params, long);
        break;
      case CURLFORM_FILE: {
	char *filename = va_arg(params, char *);
	if (current_form_info->value) {
          if (current_form_info->flags & HTTPPOST_FILENAME) {
	    if (filename) {
	      if (!(current_form_info = AddFormInfo (strdup(filename),
						     NULL, current_form_info)))
		return_value = 4;
	    }
	    else
	      return_value = 3;
          }
          else
            return_value = 2;
        }
        else {
	  if (filename)
	    current_form_info->value = strdup(filename);
	  else
	    return_value = 3;
          current_form_info->flags |= HTTPPOST_FILENAME;
        }
        break;
      }
      case CURLFORM_CONTENTTYPE: {
	char *contenttype = va_arg(params, char *);
        if (current_form_info->contenttype) {
          if (current_form_info->flags & HTTPPOST_FILENAME) {
            if (contenttype) {
              if (!(current_form_info = AddFormInfo (NULL,
                                                     strdup(contenttype),
                                                     current_form_info)))
                return_value = 4;
            }
	    else
	      return_value = 3;
          }
          else
            return_value = 2;
        }
        else {
	  if (contenttype)
	    current_form_info->contenttype = strdup(contenttype);
	  else
	    return_value = 3;
	}
        break;
      }
      default:
        fprintf (stderr, "got unknown CURLFORM_OPTION: %d\n", next_option);
        return_value = 5;
    };
  };

  /* go through the list, check for copleteness and if everything is
   * alright add the HttpPost item otherwise set return_value accordingly */
  form_info = first_form_info;
  while (form_info != NULL)
  {
    if ( (!first_form_info->name) ||
         (!form_info->value) ||
         ( (!form_info->namelength) &&
           (form_info->flags & HTTPPOST_PTRNAME) ) ||
	 ( (form_info->contentslength) &&
	   (form_info->flags & HTTPPOST_FILENAME) ) ||
	 ( (form_info->flags & HTTPPOST_FILENAME) &&
	   (form_info->flags & HTTPPOST_PTRCONTENTS) )
         ) {
      return_value = 6;
      break;
    }
    else {
      if ( (form_info->flags & HTTPPOST_FILENAME) &&
	   (!form_info->contenttype) ) {
	/* our contenttype is missing */
	form_info->contenttype
	  = strdup(ContentTypeForFilename(form_info->value, prevtype));
      }
      if ( !(form_info->flags & HTTPPOST_PTRNAME) &&
	   (form_info == first_form_info) ) {
	/* copy name (without strdup; possibly contains null characters) */
	if (AllocAndCopy(&form_info->name, form_info->namelength)) {
	  return_value = 8;
	  break;
	}
      }
      if ( !(form_info->flags & HTTPPOST_FILENAME) &&
	   !(form_info->flags & HTTPPOST_PTRCONTENTS) ) {
	/* copy value (without strdup; possibly contains null characters) */
	if (AllocAndCopy(&form_info->value, form_info->contentslength)) {
	  return_value = 8;
	  break;
	}
      }
      if ( (post = AddHttpPost (form_info->name, form_info->namelength,
                                form_info->value, form_info->contentslength,
                                form_info->contenttype, form_info->flags,
				post, httppost,
                                last_post)) == NULL) {
        return_value = 7;
      }
      if (form_info->contenttype)
	prevtype = form_info->contenttype;
    }
    form_info = form_info->more;
  };

  /* and finally delete the allocated memory */
  form_info = first_form_info;
  while (form_info != NULL) {
    FormInfo *delete_form_info;
    
    delete_form_info = form_info;
    form_info = form_info->more;
    free (delete_form_info);
  };

  return return_value;
}