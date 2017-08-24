{
      /* since nothing is written, we can just free the list of cookie file
         names */
      curl_slist_free_all(data->change.cookielist); /* clean up list */
      data->change.cookielist = NULL;
    }