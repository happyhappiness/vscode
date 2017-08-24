{
  if ((*ctx = EVP_MD_CTX_new()) == NULL)
	return (ARCHIVE_FAILED);
  EVP_DigestInit(*ctx, EVP_sha1());
  return (ARCHIVE_OK);
}