          /* the next file name starts here */
          *sep =0;
          sep++;
        }
        /* if type == NULL curl_formadd takes care of the problem */

        if(!AddMultiFiles(contp, type, filename, &multi_start,
                          &multi_current)) {
          warnf(config, "Error building form post!\n");
          free(contents);
          FreeMultiInfo(multi_start);
          return 3;
        }
        contp = sep; /* move the contents pointer to after the separator */

      } while(sep && *sep); /* loop if there's another file name */

      /* now we add the multiple files section */
      if(multi_start) {
        struct curl_forms *forms = NULL;
        struct multi_files *ptr = multi_start;
        unsigned int i, count = 0;
        while(ptr) {
          ptr = ptr->next;
          ++count;
        }
        forms = malloc((count+1)*sizeof(struct curl_forms));
        if(!forms)
        {
          fprintf(config->errors, "Error building form post!\n");
          free(contents);
          FreeMultiInfo(multi_start);
          return 4;
        }
        for(i = 0, ptr = multi_start; i < count; ++i, ptr = ptr->next)
        {
          forms[i].option = ptr->form.option;
          forms[i].value = ptr->form.value;
        }
        forms[count].option = CURLFORM_END;
        FreeMultiInfo(multi_start);
        if(curl_formadd(httppost, last_post,
                        CURLFORM_COPYNAME, name,
                        CURLFORM_ARRAY, forms, CURLFORM_END) != 0) {
          warnf(config, "curl_formadd failed!\n");
          free(forms);
          free(contents);
          return 5;
        }
        free(forms);
