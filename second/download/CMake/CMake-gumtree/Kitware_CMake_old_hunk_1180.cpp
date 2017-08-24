  lnp = (linkname_t *)calloc(1, sizeof(linkname_t));
  if (lnp == NULL)
    return -1;
  strlcpy(lnp->ln_save, th_get_pathname(t), sizeof(lnp->ln_save));
  strlcpy(lnp->ln_real, realname, sizeof(lnp->ln_real));
#ifdef DEBUG
  printf("tar_extract_file(): calling libtar_hash_add(): key=\"%s\", "
         "value=\"%s\"\n", th_get_pathname(t), realname);
#endif
  if (libtar_hash_add(t->h, lnp) != 0)
    return -1;

