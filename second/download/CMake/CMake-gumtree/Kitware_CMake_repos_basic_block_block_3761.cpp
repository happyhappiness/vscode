f(0 == strlen(uri_path) || uri_path[0] != '/') {
    free(uri_path);
    uri_path = strdup("/");
    if(!uri_path)
      return FALSE;
  }