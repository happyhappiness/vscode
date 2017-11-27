static int submit_wafl_data(const char *hostname,
                            const char *instance, /* {{{ */
                            cfg_wafl_t *old_data, const cfg_wafl_t *new_data,
                            cdtime_t interval) {
  /* Submit requested counters */
  if (HAS_ALL_FLAGS(old_data->flags,
                    CFG_WAFL_NAME_CACHE | HAVE_WAFL_NAME_CACHE) &&
      HAS_ALL_FLAGS(new_data->flags, HAVE_WAFL_NAME_CACHE))
    submit_cache_ratio(hostname, instance, "name_cache_hit",
                       new_data->name_cache_hit, new_data->name_cache_miss,
                       old_data->name_cache_hit, old_data->name_cache_miss,
                       new_data->timestamp, interval);

  if (HAS_ALL_FLAGS(old_data->flags, CFG_WAFL_DIR_CACHE | HAVE_WAFL_FIND_DIR) &&
      HAS_ALL_FLAGS(new_data->flags, HAVE_WAFL_FIND_DIR))
    submit_cache_ratio(hostname, instance, "find_dir_hit",
                       new_data->find_dir_hit, new_data->find_dir_miss,
                       old_data->find_dir_hit, old_data->find_dir_miss,
                       new_data->timestamp, interval);

  if (HAS_ALL_FLAGS(old_data->flags, CFG_WAFL_BUF_CACHE | HAVE_WAFL_BUF_HASH) &&
      HAS_ALL_FLAGS(new_data->flags, HAVE_WAFL_BUF_HASH))
    submit_cache_ratio(hostname, instance, "buf_hash_hit",
                       new_data->buf_hash_hit, new_data->buf_hash_miss,
                       old_data->buf_hash_hit, old_data->buf_hash_miss,
                       new_data->timestamp, interval);

  if (HAS_ALL_FLAGS(old_data->flags,
                    CFG_WAFL_INODE_CACHE | HAVE_WAFL_INODE_CACHE) &&
      HAS_ALL_FLAGS(new_data->flags, HAVE_WAFL_INODE_CACHE))
    submit_cache_ratio(hostname, instance, "inode_cache_hit",
                       new_data->inode_cache_hit, new_data->inode_cache_miss,
                       old_data->inode_cache_hit, old_data->inode_cache_miss,
                       new_data->timestamp, interval);

  /* Clear old HAVE_* flags */
  old_data->flags &= ~HAVE_WAFL_ALL;

  /* Copy all counters */
  old_data->timestamp = new_data->timestamp;
  old_data->name_cache_hit = new_data->name_cache_hit;
  old_data->name_cache_miss = new_data->name_cache_miss;
  old_data->find_dir_hit = new_data->find_dir_hit;
  old_data->find_dir_miss = new_data->find_dir_miss;
  old_data->buf_hash_hit = new_data->buf_hash_hit;
  old_data->buf_hash_miss = new_data->buf_hash_miss;
  old_data->inode_cache_hit = new_data->inode_cache_hit;
  old_data->inode_cache_miss = new_data->inode_cache_miss;

  /* Copy HAVE_* flags */
  old_data->flags |= (new_data->flags & HAVE_WAFL_ALL);

  return 0;
}