static int tt_read(void) {
  gauge_t rnum, size;

  tt_open_db();
  if (rdb == NULL)
    return -1;

  rnum = tcrdbrnum(rdb);
  tt_submit(rnum, "records");

  size = tcrdbsize(rdb);
  tt_submit(size, "file_size");

  return 0;
}