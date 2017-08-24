{
  if (pwd == NULL)
    return;

  uv__free(pwd->username);
  uv__free(pwd->homedir);
  pwd->username = NULL;
  pwd->homedir = NULL;
}