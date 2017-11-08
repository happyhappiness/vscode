static struct curl_hash *sh_init(void)
{
  return Curl_hash_alloc(CURL_SOCKET_HASH_TABLE_SIZE, hash_fd, fd_key_compare,
                         sh_freeentry);
}