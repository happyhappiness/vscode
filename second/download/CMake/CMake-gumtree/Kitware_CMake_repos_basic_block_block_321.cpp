{
              field = (field==last_on_page) ? first : field + 1;
              if (((*field)->opts & O_VISIBLE))
                break;
            }