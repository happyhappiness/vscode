int formparse(struct OperationConfig *config,
              const char *input,
              struct curl_httppost **httppost,
              struct curl_httppost **last_post,
              bool literal_value)
{
  /* nextarg MUST be a string in the format 'name=contents' and we'll
     build a linked list with the info */
  char name[256];
  char *contents = NULL;
  char type_major[128] = "";
  char type_minor[128] = "";
  char *contp;
  char *type = NULL;
  char *sep;

  if((1 == sscanf(input, "%255[^=]=", name)) &&
     ((contp = strchr(input, '=')) != NULL)) {
    /* the input was using the correct format */

    /* Allocate the contents */
    contents = strdup(contp+1);
    if(!contents) {
      fprintf(config->global->errors, "out of memory\n");
      return 1;
    }
    contp = contents;

    if('@' == contp[0] && !literal_value) {

      /* we use the @-letter to indicate file name(s) */

      struct multi_files *multi_start = NULL;
      struct multi_files *multi_current = NULL;

      char *ptr = contp;
      char *end = ptr + strlen(ptr);

      do {
        /* since this was a file, it may have a content-type specifier
           at the end too, or a filename. Or both. */
        char *filename = NULL;
        char *word_end;
        bool semicolon;

        type = NULL;

        ++ptr;
        contp = get_param_word(&ptr, &word_end);
        semicolon = (';' == *ptr) ? TRUE : FALSE;
        *word_end = '\0'; /* terminate the contp */

        /* have other content, continue parse */
        while(semicolon) {
          /* have type or filename field */
          ++ptr;
          while(*ptr && (ISSPACE(*ptr)))
            ++ptr;

          if(checkprefix("type=", ptr)) {
            /* set type pointer */
            type = &ptr[5];

            /* verify that this is a fine type specifier */
            if(2 != sscanf(type, "%127[^/]/%127[^;,\n]",
                           type_major, type_minor)) {
              warnf(config->global,
                    "Illegally formatted content-type field!\n");
              Curl_safefree(contents);
              FreeMultiInfo(&multi_start, &multi_current);
              return 2; /* illegal content-type syntax! */
            }

            /* now point beyond the content-type specifier */
            sep = type + strlen(type_major)+strlen(type_minor)+1;

            /* there's a semicolon following - we check if it is a filename
               specified and if not we simply assume that it is text that
               the user wants included in the type and include that too up
               to the next sep. */
            ptr = sep;
            if(*sep==';') {
              if(!checkprefix(";filename=", sep)) {
                ptr = sep + 1;
                (void)get_param_word(&ptr, &sep);
                semicolon = (';' == *ptr) ? TRUE : FALSE;
              }
            }
            else
              semicolon = FALSE;

            if(*sep)
              *sep = '\0'; /* zero terminate type string */
          }
          else if(checkprefix("filename=", ptr)) {
            ptr += 9;
            filename = get_param_word(&ptr, &word_end);
            semicolon = (';' == *ptr) ? TRUE : FALSE;
            *word_end = '\0';
          }
          else {
            /* unknown prefix, skip to next block */
            char *unknown = NULL;
            unknown = get_param_word(&ptr, &word_end);
            semicolon = (';' == *ptr) ? TRUE : FALSE;
            if(*unknown) {
              *word_end = '\0';
              warnf(config->global, "skip unknown form field: %s\n", unknown);
            }
          }
        }
        /* now ptr point to comma or string end */


        /* if type == NULL curl_formadd takes care of the problem */

        if(*contp && !AddMultiFiles(contp, type, filename, &multi_start,
                          &multi_current)) {
          warnf(config->global, "Error building form post!\n");
          Curl_safefree(contents);
          FreeMultiInfo(&multi_start, &multi_current);
          return 3;
        }

        /* *ptr could be '\0', so we just check with the string end */
      } while(ptr < end); /* loop if there's another file name */

      /* now we add the multiple files section */
      if(multi_start) {
        struct curl_forms *forms = NULL;
        struct multi_files *start = multi_start;
        unsigned int i, count = 0;
        while(start) {
          start = start->next;
          ++count;
        }
        forms = malloc((count+1)*sizeof(struct curl_forms));
        if(!forms) {
          fprintf(config->global->errors, "Error building form post!\n");
          Curl_safefree(contents);
          FreeMultiInfo(&multi_start, &multi_current);
          return 4;
        }
        for(i = 0, start = multi_start; i < count; ++i, start = start->next) {
          forms[i].option = start->form.option;
          forms[i].value = start->form.value;
        }
        forms[count].option = CURLFORM_END;
        FreeMultiInfo(&multi_start, &multi_current);
        if(curl_formadd(httppost, last_post,
                        CURLFORM_COPYNAME, name,
                        CURLFORM_ARRAY, forms, CURLFORM_END) != 0) {
          warnf(config->global, "curl_formadd failed!\n");
          Curl_safefree(forms);
          Curl_safefree(contents);
          return 5;
        }
        Curl_safefree(forms);
      }
    }
    else {
      struct curl_forms info[4];
      int i = 0;
      char *ct = literal_value ? NULL : strstr(contp, ";type=");

      info[i].option = CURLFORM_COPYNAME;
      info[i].value = name;
      i++;

      if(ct) {
        info[i].option = CURLFORM_CONTENTTYPE;
        info[i].value = &ct[6];
        i++;
        ct[0] = '\0'; /* zero terminate here */
      }

      if(contp[0]=='<' && !literal_value) {
        info[i].option = CURLFORM_FILECONTENT;
        info[i].value = contp+1;
        i++;
        info[i].option = CURLFORM_END;

        if(curl_formadd(httppost, last_post,
                        CURLFORM_ARRAY, info, CURLFORM_END) != 0) {
          warnf(config->global, "curl_formadd failed, possibly the file %s is "
                "bad!\n", contp + 1);
          Curl_safefree(contents);
          return 6;
        }
      }
      else {
#ifdef CURL_DOES_CONVERSIONS
        if(convert_to_network(contp, strlen(contp))) {
          warnf(config->global, "curl_formadd failed!\n");
          Curl_safefree(contents);
          return 7;
        }
#endif
        info[i].option = CURLFORM_COPYCONTENTS;
        info[i].value = contp;
        i++;
        info[i].option = CURLFORM_END;
        if(curl_formadd(httppost, last_post,
                        CURLFORM_ARRAY, info, CURLFORM_END) != 0) {
          warnf(config->global, "curl_formadd failed!\n");
          Curl_safefree(contents);
          return 8;
        }
      }
    }

  }
  else {
    warnf(config->global, "Illegally formatted input field!\n");
    return 1;
  }
  Curl_safefree(contents);
  return 0;
}