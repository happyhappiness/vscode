            file = fopen(nextarg, "rb");
            if(!file)
              warnf(config, "Couldn't read data from file \"%s\", this makes "
                    "an empty POST.\n", nextarg);
          }

          if(subletter == 'b') /* forced binary */
            postdata = file2memory(file, &config->postfieldsize);
          else
            postdata = file2string(file);

          if(file && (file != stdin))
            fclose(file);

          if(!postdata) {
            /* no data from the file, point to a zero byte string to make this
               get sent as a POST anyway */
            postdata=strdup("");
          }
