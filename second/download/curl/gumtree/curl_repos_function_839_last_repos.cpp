static metalink_checksum *new_metalink_checksum_from_hex_digest
(const metalink_digest_def *digest_def, const char *hex_digest)
{
  metalink_checksum *chksum;
  unsigned char *digest;
  size_t i;
  size_t len = strlen(hex_digest);
  digest = malloc(len/2);
  if(!digest)
    return 0;

  for(i = 0; i < len; i += 2) {
    digest[i/2] = hex_to_uint(hex_digest + i);
  }
  chksum = malloc(sizeof(metalink_checksum));
  if(chksum) {
    chksum->digest_def = digest_def;
    chksum->digest = digest;
  }
  return chksum;
}