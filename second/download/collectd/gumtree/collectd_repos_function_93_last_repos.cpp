static int get_block_stats(struct block_device *block_dev) {

  if (!block_dev) {
    ERROR(PLUGIN_NAME " plugin: get_block_stats NULL pointer");
    return -1;
  }

  struct lv_block_info binfo;
  init_block_info(&binfo);

  if (lv_domain_block_info(block_dev->dom, block_dev->path, &binfo) < 0) {
    ERROR(PLUGIN_NAME " plugin: lv_domain_block_info failed");
    return -1;
  }

  disk_submit(&binfo, block_dev->dom, block_dev->path);
  return 0;
}