static void delete_metalink_checksum(metalink_checksum *chksum)
{
  if(chksum == NULL) {
    return;
  }
  Curl_safefree(chksum->digest);
  Curl_safefree(chksum);
}