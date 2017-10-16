            file = fopen(nextarg, "rb");
            if(!file)
              warnf(config, "Couldn't read data from file \"%s\", this makes "
                    "an empty POST.\n", nextarg);
          }

          if(subletter == 'b') {
            /* forced binary */
            err = file2memory(&postdata, &size, file);
            config->postfieldsize = (curl_off_t)size;
          }
          else
            err = file2string(&postdata, file);

          if(file && (file != stdin))
            fclose(file);
          if(err)
            return err;

          if(!postdata) {
            /* no data from the file, point to a zero byte string to make this
               get sent as a POST anyway */
            postdata=strdup("");
          }
