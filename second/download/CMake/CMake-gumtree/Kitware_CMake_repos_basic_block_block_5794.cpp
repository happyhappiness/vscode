{
        /* Allocate an empty string instead of returning NULL as user name */
        user = strdup("");
        if(!user)
          result = CURLE_OUT_OF_MEMORY;
      }