static void init_lv_info(struct lv_info *info) {
  if (info != NULL)
    memset(info, 0, sizeof(*info));
}