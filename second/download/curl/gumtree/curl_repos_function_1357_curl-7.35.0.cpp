static size_t hash_fd(void *key, size_t key_length, size_t slots_num)
{
  int fd = *((int *) key);
  (void) key_length;

  return (fd % (int)slots_num);
}