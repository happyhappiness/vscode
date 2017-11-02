static
long chunk_bgn(const struct curl_fileinfo *finfo, void *ptr, int remains)
{
  chunk_data_t *ch_d = ptr;
  ch_d->remains = remains;

  printf("=============================================================\n");
  printf("Remains:      %d\n", remains);
  printf("Filename:     %s\n", finfo->filename);
  if(finfo->strings.perm) {
    printf("Permissions:  %s", finfo->strings.perm);
    if(finfo->flags & CURLFINFOFLAG_KNOWN_PERM)
      printf(" (parsed => %o)", finfo->perm);
    printf("\n");
  }
  printf("Size:         %ldB\n", (long)finfo->size);
  if(finfo->strings.user)
    printf("User:         %s\n", finfo->strings.user);
  if(finfo->strings.group)
    printf("Group:        %s\n", finfo->strings.group);
  if(finfo->strings.time)
    printf("Time:         %s\n", finfo->strings.time);
  printf("Filetype:     ");
  switch(finfo->filetype) {
  case CURLFILETYPE_FILE:
    printf("regular file\n");
    break;
  case CURLFILETYPE_DIRECTORY:
    printf("directory\n");
    break;
  case CURLFILETYPE_SYMLINK:
    printf("symlink\n");
    printf("Target:       %s\n", finfo->strings.target);
    break;
  default:
    printf("other type\n");
    break;
  }
  if(finfo->filetype == CURLFILETYPE_FILE) {
    ch_d->print_content = 1;
    printf("Content:\n-------------------------------------------------------------\n");
  }
  if(strcmp(finfo->filename, "someothertext.txt") == 0) {
    printf("# THIS CONTENT WAS SKIPPED IN CHUNK_BGN CALLBACK #\n");
    return CURL_CHUNK_BGN_FUNC_SKIP;
  }
  return CURL_CHUNK_BGN_FUNC_OK;
}