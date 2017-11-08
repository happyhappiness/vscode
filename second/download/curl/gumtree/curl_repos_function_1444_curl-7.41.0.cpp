static void sh_delentry(struct curl_hash *sh, curl_socket_t s)
{
  struct Curl_sh_entry *there =
    Curl_hash_pick(sh, (char *)&s, sizeof(curl_socket_t));

  if(there) {
    /* this socket is in the hash */
    /* We remove the hash entry. (This'll end up in a call to
       sh_freeentry().) */
    Curl_hash_delete(sh, (char *)&s, sizeof(curl_socket_t));
  }
}