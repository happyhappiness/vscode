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

