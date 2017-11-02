static struct curl_hash *sh_init(int hashsize)
{
  return Curl_hash_alloc(hashsize, hash_fd, fd_key_compare,
                         sh_freeentry);
}