static
CURLFORMcode FormAdd(struct curl_httppost **httppost,
                     struct curl_httppost **last_post,
                     va_list params)
{
  FormInfo *first_form, *current_form, *form = NULL;
  CURLFORMcode return_value = CURL_FORMADD_OK;
  const char *prevtype = NULL;
  struct curl_httppost *post = NULL;
  CURLformoption option;
  struct curl_forms *forms = NULL;
  char *array_value=NULL; /* value read from an array */

  /* This is a state variable, that if TRUE means that we're parsing an
     array that we got passed to us. If FALSE we're parsing the input
     va_list arguments. */
  bool array_state = FALSE;

  /*
   * We need to allocate the first struct to fill in.
   */
  first_form = (FormInfo *)calloc(sizeof(struct FormInfo), 1);
  if(!first_form)
    return CURL_FORMADD_MEMORY;

  current_form = first_form;

  /*
   * Loop through all the options set. Break if we have an error to report.
   */
  while (return_value == CURL_FORMADD_OK) {

    /* first see if we have more parts of the array param */
    if ( array_state ) {
      /* get the upcoming option from the given array */
      option = forms->option;
      array_value = (char *)forms->value;

      forms++; /* advance this to next entry */
      if (CURLFORM_END == option) {
        /* end of array state */
        array_state = FALSE;
        continue;
      }
    }
    else {
      /* This is not array-state, get next option */
      option = va_arg(params, CURLformoption);
      if (CURLFORM_END == option)
        break;
    }

    switch (option) {
    case CURLFORM_ARRAY:
      if(array_state)
        /* we don't support an array from within an array */
        return_value = CURL_FORMADD_ILLEGAL_ARRAY;
      else {
        forms = va_arg(params, struct curl_forms *);
        if (forms)
          array_state = TRUE;
        else
          return_value = CURL_FORMADD_NULL;
      }
      break;

      /*
       * Set the Name property.
       */
    case CURLFORM_PTRNAME:
      current_form->flags |= HTTPPOST_PTRNAME; /* fall through */
    case CURLFORM_COPYNAME:
      if (current_form->name)
        return_value = CURL_FORMADD_OPTION_TWICE;
      else {
        char *name = array_state?
          array_value:va_arg(params, char *);
        if (name)
          current_form->name = name; /* store for the moment */
        else
          return_value = CURL_FORMADD_NULL;
      }
      break;
    case CURLFORM_NAMELENGTH:
      if (current_form->namelength)
        return_value = CURL_FORMADD_OPTION_TWICE;
      else
        current_form->namelength =
          array_state?(long)array_value:(long)va_arg(params, long);
      break;

      /*
       * Set the contents property.
       */
    case CURLFORM_PTRCONTENTS:
      current_form->flags |= HTTPPOST_PTRCONTENTS; /* fall through */
    case CURLFORM_COPYCONTENTS:
      if (current_form->value)
        return_value = CURL_FORMADD_OPTION_TWICE;
      else {
        char *value =
          array_state?array_value:va_arg(params, char *);
        if (value)
          current_form->value = value; /* store for the moment */
        else
          return_value = CURL_FORMADD_NULL;
      }
      break;
    case CURLFORM_CONTENTSLENGTH:
      if (current_form->contentslength)
        return_value = CURL_FORMADD_OPTION_TWICE;
      else
        current_form->contentslength =
          array_state?(long)array_value:va_arg(params, long);
      break;

      /* Get contents from a given file name */
    case CURLFORM_FILECONTENT:
      if (current_form->flags != 0)
        return_value = CURL_FORMADD_OPTION_TWICE;
      else {
        char *filename = array_state?
          array_value:va_arg(params, char *);
        if (filename) {
          current_form->value = strdup(filename);
          if(!current_form->value)
            return_value = CURL_FORMADD_MEMORY;
          else {
            current_form->flags |= HTTPPOST_READFILE;
            current_form->value_alloc = TRUE;
          }
        }
        else
          return_value = CURL_FORMADD_NULL;
      }
      break;

      /* We upload a file */
    case CURLFORM_FILE:
      {
        char *filename = array_state?array_value:
          va_arg(params, char *);

        if (current_form->value) {
          if (current_form->flags & HTTPPOST_FILENAME) {
            if (filename) {
              if (!(current_form = AddFormInfo(strdup(filename),
                                               NULL, current_form)))
                return_value = CURL_FORMADD_MEMORY;
            }
            else
              return_value = CURL_FORMADD_NULL;
          }
          else
            return_value = CURL_FORMADD_OPTION_TWICE;
        }
        else {
          if (filename) {
            current_form->value = strdup(filename);
            if(!current_form->value)
              return_value = CURL_FORMADD_MEMORY;
            else {
              current_form->flags |= HTTPPOST_FILENAME;
              current_form->value_alloc = TRUE;
            }
          }
          else
            return_value = CURL_FORMADD_NULL;
        }
        break;
      }

    case CURLFORM_BUFFER:
      {
        char *filename = array_state?array_value:
          va_arg(params, char *);

        if (current_form->value) {
          if (current_form->flags & HTTPPOST_BUFFER) {
            if (filename) {
              if (!(current_form = AddFormInfo(strdup(filename),
                                               NULL, current_form)))
                return_value = CURL_FORMADD_MEMORY;
            }
            else
              return_value = CURL_FORMADD_NULL;
          }
          else
            return_value = CURL_FORMADD_OPTION_TWICE;
        }
        else {
          if (filename) {
            current_form->value = strdup(filename);
            if(!current_form->value)
              return_value = CURL_FORMADD_MEMORY;
          }
          else
            return_value = CURL_FORMADD_NULL;
          current_form->flags |= HTTPPOST_BUFFER;
        }
        break;
      }

    case CURLFORM_BUFFERPTR:
        current_form->flags |= HTTPPOST_PTRBUFFER;
      if (current_form->buffer)
        return_value = CURL_FORMADD_OPTION_TWICE;
      else {
        char *buffer =
          array_state?array_value:va_arg(params, char *);
        if (buffer)
          current_form->buffer = buffer; /* store for the moment */
        else
          return_value = CURL_FORMADD_NULL;
      }
      break;

    case CURLFORM_BUFFERLENGTH:
      if (current_form->bufferlength)
        return_value = CURL_FORMADD_OPTION_TWICE;
      else
        current_form->bufferlength =
          array_state?(long)array_value:va_arg(params, long);
      break;

    case CURLFORM_CONTENTTYPE:
      {
        char *contenttype =
          array_state?array_value:va_arg(params, char *);
        if (current_form->contenttype) {
          if (current_form->flags & HTTPPOST_FILENAME) {
            if (contenttype) {
              if (!(current_form = AddFormInfo(NULL,
                                               strdup(contenttype),
                                               current_form)))
                return_value = CURL_FORMADD_MEMORY;
            }
            else
              return_value = CURL_FORMADD_NULL;
          }
          else
            return_value = CURL_FORMADD_OPTION_TWICE;
        }
        else {
          if (contenttype) {
            current_form->contenttype = strdup(contenttype);
            if(!current_form->contenttype)
              return_value = CURL_FORMADD_MEMORY;
            else
              current_form->contenttype_alloc = TRUE;
          }
          else
            return_value = CURL_FORMADD_NULL;
        }
        break;
      }
    case CURLFORM_CONTENTHEADER:
      {
        /* this "cast increases required alignment of target type" but
           we consider it OK anyway */
        struct curl_slist* list = array_state?
          (struct curl_slist*)array_value:
          va_arg(params, struct curl_slist*);

        if( current_form->contentheader )
          return_value = CURL_FORMADD_OPTION_TWICE;
        else
          current_form->contentheader = list;

        break;
      }
    case CURLFORM_FILENAME:
      {
        char *filename = array_state?array_value:
          va_arg(params, char *);
        if( current_form->showfilename )
          return_value = CURL_FORMADD_OPTION_TWICE;
        else {
          current_form->showfilename = strdup(filename);
          if(!current_form->showfilename)
            return_value = CURL_FORMADD_MEMORY;
          else
            current_form->showfilename_alloc = TRUE;
        }
        break;
      }
    default:
      return_value = CURL_FORMADD_UNKNOWN_OPTION;
    }
  }

  if(CURL_FORMADD_OK == return_value) {
    /* go through the list, check for copleteness and if everything is
     * alright add the HttpPost item otherwise set return_value accordingly */

    post = NULL;
    for(form = first_form;
        form != NULL;
        form = form->more) {
      if ( ((!form->name || !form->value) && !post) ||
           ( (form->contentslength) &&
             (form->flags & HTTPPOST_FILENAME) ) ||
           ( (form->flags & HTTPPOST_FILENAME) &&
             (form->flags & HTTPPOST_PTRCONTENTS) ) ||

           ( (!form->buffer) &&
             (form->flags & HTTPPOST_BUFFER) &&
             (form->flags & HTTPPOST_PTRBUFFER) ) ||

           ( (form->flags & HTTPPOST_READFILE) &&
             (form->flags & HTTPPOST_PTRCONTENTS) )
           ) {
        return_value = CURL_FORMADD_INCOMPLETE;
        break;
      }
      else {
        if ( ((form->flags & HTTPPOST_FILENAME) ||
              (form->flags & HTTPPOST_BUFFER)) &&
             !form->contenttype ) {
          /* our contenttype is missing */
          form->contenttype
            = strdup(ContentTypeForFilename(form->value, prevtype));
          if(!form->contenttype) {
            return_value = CURL_FORMADD_MEMORY;
            break;
          }
          form->contenttype_alloc = TRUE;
        }
        if ( !(form->flags & HTTPPOST_PTRNAME) &&
             (form == first_form) ) {
          /* copy name (without strdup; possibly contains null characters) */
          form->name = memdup(form->name, form->namelength);
          if (!form->name) {
            return_value = CURL_FORMADD_MEMORY;
            break;
          }
          form->name_alloc = TRUE;
        }
        if ( !(form->flags & HTTPPOST_FILENAME) &&
             !(form->flags & HTTPPOST_READFILE) &&
             !(form->flags & HTTPPOST_PTRCONTENTS) &&
             !(form->flags & HTTPPOST_PTRBUFFER) ) {
          /* copy value (without strdup; possibly contains null characters) */
          form->value = memdup(form->value, form->contentslength);
          if (!form->value) {
            return_value = CURL_FORMADD_MEMORY;
            break;
          }
          form->value_alloc = TRUE;
        }
        post = AddHttpPost(form->name, form->namelength,
                           form->value, form->contentslength,
                           form->buffer, form->bufferlength,
                           form->contenttype, form->flags,
                           form->contentheader, form->showfilename,
                           post, httppost,
                           last_post);

        if(!post) {
          return_value = CURL_FORMADD_MEMORY;
          break;
        }

        if (form->contenttype)
          prevtype = form->contenttype;
      }
    }
  }

  if(return_value) {
    /* we return on error, free possibly allocated fields */
    if(!form)
      form = current_form;
    if(form) {
      if(form->name_alloc)
        free(form->name);
      if(form->value_alloc)
        free(form->value);
      if(form->contenttype_alloc)
        free(form->contenttype);
      if(form->showfilename_alloc)
        free(form->showfilename);
    }
  }

  /* always delete the allocated memory before returning */
  form = first_form;
  while (form != NULL) {
    FormInfo *delete_form;

    delete_form = form;
    form = form->more;
    free (delete_form);
  }

  return return_value;
}