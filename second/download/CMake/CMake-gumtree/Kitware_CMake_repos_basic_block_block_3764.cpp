{
    /* Let cookie-path be the default-path. */
    free(new_path);
    new_path = strdup("/");
    return new_path;
  }