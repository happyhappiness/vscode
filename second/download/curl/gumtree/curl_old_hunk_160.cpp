          FILE *file;

          nextarg++; /* pass the @ */

          if(curlx_strequal("-", nextarg))
            file = stdin;
          else
            file = fopen(nextarg, "rb");

          if(subletter == 'b') /* forced binary */
            postdata = file2memory(file, &config->postfieldsize);
          else
            postdata = file2string(file);
          if(file && (file != stdin))
            fclose(file);
        }
        else {
          GetStr(&postdata, nextarg);
        }

        if(config->postfields) {
