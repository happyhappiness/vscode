static uint64_t ovs_uid_generate() {
  uint64_t new_uid;
  pthread_mutex_lock(&ovs_uid_mutex);
  new_uid = ++ovs_uid;
  pthread_mutex_unlock(&ovs_uid_mutex);
  return new_uid;
}