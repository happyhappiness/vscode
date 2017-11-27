static void ps_fill_details(const procstat_t *ps, procstat_entry_t *entry) {
  if (entry->has_io == 0 && ps_read_io(entry) != 0) {
    /* no io data */
    entry->io_rchar = -1;
    entry->io_wchar = -1;
    entry->io_syscr = -1;
    entry->io_syscw = -1;

    DEBUG("ps_read_process: not get io data for pid %li", entry->id);
  }
  entry->has_io = 1;

  if (report_ctx_switch) {
    if (entry->has_cswitch == 0 && ps_read_tasks_status(entry) != 0) {
      entry->cswitch_vol = -1;
      entry->cswitch_invol = -1;

      DEBUG("ps_read_tasks_status: not get context "
            "switch data for pid %li",
            entry->id);
    }
    entry->has_cswitch = 1;
  }
}