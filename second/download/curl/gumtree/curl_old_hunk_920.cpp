          if(subletter == 'b') /* forced data-binary */
            set_binmode(stdin);
        }
        else {
          file = fopen(nextarg, "rb");
          if(!file)
            warnf(config, "Couldn't read data from file \"%s\", this makes "
                  "an empty POST.\n", nextarg);
        }

        if(subletter == 'b')
          /* forced binary */
          err = file2memory(&postdata, &size, file);
