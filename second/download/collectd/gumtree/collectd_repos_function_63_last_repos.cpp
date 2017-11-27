static void init_block_info(struct lv_block_info *binfo) {
  if (binfo == NULL)
    return;

  binfo->bi.rd_req = -1;
  binfo->bi.wr_req = -1;
  binfo->bi.rd_bytes = -1;
  binfo->bi.wr_bytes = -1;

  binfo->rd_total_times = -1;
  binfo->wr_total_times = -1;
  binfo->fl_req = -1;
  binfo->fl_total_times = -1;
}