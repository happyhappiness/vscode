static void ps_fill_details(const procstat_t *ps, process_entry_t *entry) {
  if (entry->has_io == 0) {
    ps_read_io(entry);
    entry->has_io = 1;
  }

  if (ps->report_ctx_switch) {
    if (entry->has_cswitch == 0) {
      ps_read_tasks_status(entry);
      entry->has_cswitch = 1;
    }
  }

  if (ps->report_maps_num) {
    int num_maps;
    if (entry->has_maps == 0 && (num_maps = ps_count_maps(entry->id)) > 0) {
      entry->num_maps = num_maps;
    }
    entry->has_maps = 1;
  }

  if (ps->report_fd_num) {
    int num_fd;
    if (entry->has_fd == 0 && (num_fd = ps_count_fd(entry->id)) > 0) {
      entry->num_fd = num_fd;
    }
    entry->has_fd = 1;
  }
}