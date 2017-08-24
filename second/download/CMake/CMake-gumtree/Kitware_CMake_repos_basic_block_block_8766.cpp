{
  if ((*ctx = EVP_MD_CTX_new()) == NULL)
	return (ARCHIVE_FAILED);
  EVP_DigestInit(*ctx, EVP_md5());
  return (ARCHIVE_OK);
}