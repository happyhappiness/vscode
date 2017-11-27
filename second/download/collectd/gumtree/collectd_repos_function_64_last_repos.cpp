static int get_block_info(struct lv_block_info *binfo,
                          virTypedParameterPtr param, int nparams) {
  if (binfo == NULL || param == NULL)
    return -1;

  for (int i = 0; i < nparams; ++i) {
    /* ignore type. Everything must be LLONG anyway. */
    GET_BLOCK_INFO_VALUE("rd_operations", bi.rd_req);
    GET_BLOCK_INFO_VALUE("wr_operations", bi.wr_req);
    GET_BLOCK_INFO_VALUE("rd_bytes", bi.rd_bytes);
    GET_BLOCK_INFO_VALUE("wr_bytes", bi.wr_bytes);
    GET_BLOCK_INFO_VALUE("rd_total_times", rd_total_times);
    GET_BLOCK_INFO_VALUE("wr_total_times", wr_total_times);
    GET_BLOCK_INFO_VALUE("flush_operations", fl_req);
    GET_BLOCK_INFO_VALUE("flush_total_times", fl_total_times);
  }

  return 0;
}