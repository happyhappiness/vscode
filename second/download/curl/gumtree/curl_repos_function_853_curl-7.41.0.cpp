int fwrite_xattr(CURL *curl, int fd)
{
  int i = 0;
  int err = 0;

  /* loop through all xattr-curlinfo pairs and abort on a set error */
  while(err == 0 && mappings[i].attr != NULL) {
    char *value = NULL;
    CURLcode result = curl_easy_getinfo(curl, mappings[i].info, &value);
    if(!result && value) {
#ifdef HAVE_FSETXATTR_6
      err = fsetxattr(fd, mappings[i].attr, value, strlen(value), 0, 0);
#elif defined(HAVE_FSETXATTR_5)
      err = fsetxattr(fd, mappings[i].attr, value, strlen(value), 0);
#elif defined(__FreeBSD_version)
      err = extattr_set_fd(fd, EXTATTR_NAMESPACE_USER, mappings[i].attr, value,
                           strlen(value));
      /* FreeBSD's extattr_set_fd returns the length of the extended attribute
       */
      err = err < 0 ? err : 0;
#endif
    }
    i++;
  }

  return err;
}