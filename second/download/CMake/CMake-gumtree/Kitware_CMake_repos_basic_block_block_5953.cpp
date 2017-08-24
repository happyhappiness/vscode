{
    *fragment = 0;

    /* we know the path part ended with a fragment, so we know the full URL
       string does too and we need to cut it off from there so it isn't used
       over proxy */
    fragment = strchr(data->change.url, '#');
    if(fragment)
      *fragment = 0;
  }