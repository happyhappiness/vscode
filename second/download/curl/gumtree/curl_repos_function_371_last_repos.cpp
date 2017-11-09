CURLFORMcode
curl_formadd_ccsid(struct curl_httppost * * httppost,
                   struct curl_httppost * * last_post, ...)

{
  va_list arg;
  CURLformoption option;
  CURLFORMcode result;
  struct curl_forms * forms;
  struct curl_forms * lforms;
  struct curl_forms * tforms;
  unsigned int lformlen;
  const char * value;
  unsigned int ccsid;
  int nargs;
  int namex;
  int namelengthx;
  int contentx;
  int lengthx;
  unsigned int contentccsid;
  unsigned int nameccsid;

  /* A single curl_formadd() call cannot be split in several calls to deal
     with all parameters: the original parameters are thus copied to a local
     curl_forms array and converted to ASCII when needed.
     CURLFORM_PTRNAME is processed as if it were CURLFORM_COPYNAME.
     CURLFORM_COPYNAME and CURLFORM_NAMELENGTH occurrence order in
     parameters is not defined; for this reason, the actual conversion is
     delayed to the end of parameter processing. The same applies to
     CURLFORM_COPYCONTENTS/CURLFORM_CONTENTSLENGTH, but these may appear
     several times in the parameter list; the problem resides here in knowing
     which CURLFORM_CONTENTSLENGTH applies to which CURLFORM_COPYCONTENTS and
     when we can be sure to have both info for conversion: end of parameter
     list is such a point, but CURLFORM_CONTENTTYPE is also used here as a
     natural separator between content data definitions; this seems to be
     in accordance with FormAdd() behavior. */

  /* Allocate the local curl_forms array. */

  lformlen = ALLOC_GRANULE;
  lforms = malloc(lformlen * sizeof *lforms);

  if(!lforms)
    return CURL_FORMADD_MEMORY;

  /* Process the arguments, copying them into local array, latching conversion
     indexes and converting when needed. */

  result = CURL_FORMADD_OK;
  nargs = 0;
  contentx = -1;
  lengthx = -1;
  namex = -1;
  namelengthx = -1;
  forms = (struct curl_forms *) NULL;
  va_start(arg, last_post);

  for(;;) {
    /* Make sure there is still room for an item in local array. */

    if(nargs >= lformlen) {
      lformlen += ALLOC_GRANULE;
      tforms = realloc(lforms, lformlen * sizeof *lforms);

      if(!tforms) {
        result = CURL_FORMADD_MEMORY;
        break;
        }

      lforms = tforms;
      }

    /* Get next option. */

    if(forms) {
      /* Get option from array. */

      option = forms->option;
      value = forms->value;
      forms++;
      }
    else {
      /* Get option from arguments. */

      option = va_arg(arg, CURLformoption);

      if(option == CURLFORM_END)
        break;
      }

    /* Dispatch by option. */

    switch (option) {

    case CURLFORM_END:
      forms = (struct curl_forms *) NULL;       /* Leave array mode. */
      continue;

    case CURLFORM_ARRAY:
      if(!forms) {
        forms = va_arg(arg, struct curl_forms *);
        continue;
        }

      result = CURL_FORMADD_ILLEGAL_ARRAY;
      break;

    case CURLFORM_COPYNAME:
      option = CURLFORM_PTRNAME;                /* Static for now. */

    case CURLFORM_PTRNAME:
      if(namex >= 0)
        result = CURL_FORMADD_OPTION_TWICE;

      namex = nargs;

      if(!forms) {
        value = va_arg(arg, char *);
        nameccsid = (unsigned int) va_arg(arg, long);
        }
      else {
        nameccsid = (unsigned int) forms->value;
        forms++;
        }

      break;

    case CURLFORM_COPYCONTENTS:
      if(contentx >= 0)
        result = CURL_FORMADD_OPTION_TWICE;

      contentx = nargs;

      if(!forms) {
        value = va_arg(arg, char *);
        contentccsid = (unsigned int) va_arg(arg, long);
        }
      else {
        contentccsid = (unsigned int) forms->value;
        forms++;
        }

      break;

    case CURLFORM_PTRCONTENTS:
    case CURLFORM_BUFFERPTR:
      if(!forms)
        value = va_arg(arg, char *);            /* No conversion. */

      break;

    case CURLFORM_CONTENTSLENGTH:
      lengthx = nargs;

      if(!forms)
        value = (char *) va_arg(arg, long);

      break;

    case CURLFORM_CONTENTLEN:
      lengthx = nargs;

      if(!forms)
        value = (char *) va_arg(arg, curl_off_t);

      break;

    case CURLFORM_NAMELENGTH:
      namelengthx = nargs;

      if(!forms)
        value = (char *) va_arg(arg, long);

      break;

    case CURLFORM_BUFFERLENGTH:
      if(!forms)
        value = (char *) va_arg(arg, long);

      break;

    case CURLFORM_CONTENTHEADER:
      if(!forms)
        value = (char *) va_arg(arg, struct curl_slist *);

      break;

    case CURLFORM_STREAM:
      if(!forms)
        value = (char *) va_arg(arg, void *);

      break;

    case CURLFORM_CONTENTTYPE:
      /* If a previous content has been encountered, convert it now. */

      if(Curl_formadd_convert(lforms, contentx, lengthx, contentccsid) < 0) {
        result = CURL_FORMADD_MEMORY;
        break;
        }

      contentx = -1;
      lengthx = -1;
      /* Fall into default. */

    default:
      /* Must be a convertible string. */

      if(!Curl_is_formadd_string(option)) {
        result = CURL_FORMADD_UNKNOWN_OPTION;
        break;
        }

      if(!forms) {
        value = va_arg(arg, char *);
        ccsid = (unsigned int) va_arg(arg, long);
        }
      else {
        ccsid = (unsigned int) forms->value;
        forms++;
        }

      /* Do the conversion. */

      lforms[nargs].value = value;

      if(Curl_formadd_convert(lforms, nargs, -1, ccsid) < 0) {
        result = CURL_FORMADD_MEMORY;
        break;
        }

      value = lforms[nargs].value;
      }

    if(result != CURL_FORMADD_OK)
      break;

    lforms[nargs].value = value;
    lforms[nargs++].option = option;
    }

  va_end(arg);

  /* Convert the name and the last content, now that we know their lengths. */

  if(result == CURL_FORMADD_OK && namex >= 0) {
    if(Curl_formadd_convert(lforms, namex, namelengthx, nameccsid) < 0)
      result = CURL_FORMADD_MEMORY;
    else
      lforms[namex].option = CURLFORM_COPYNAME;         /* Force copy. */
    }

  if(result == CURL_FORMADD_OK) {
    if(Curl_formadd_convert(lforms, contentx, lengthx, contentccsid) < 0)
      result = CURL_FORMADD_MEMORY;
    else
      contentx = -1;
    }

  /* Do the formadd with our converted parameters. */

  if(result == CURL_FORMADD_OK) {
    lforms[nargs].option = CURLFORM_END;
    result = curl_formadd(httppost, last_post,
                          CURLFORM_ARRAY, lforms, CURLFORM_END);
    }

  /* Terminate. */

  Curl_formadd_release_local(lforms, nargs, contentx);
  return result;
}