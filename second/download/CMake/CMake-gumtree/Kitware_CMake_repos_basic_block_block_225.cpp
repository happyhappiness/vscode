(changed_opts & O_VISIBLE)
                {
                  if (newopts & O_VISIBLE)
                    res = Display_Field(field);
                  else
                    res = Erase_Field(field);
                }
              else
                {
                  if ((changed_opts & O_PUBLIC) &&
                      (newopts & O_VISIBLE))
                    res = Display_Field(field);
                }