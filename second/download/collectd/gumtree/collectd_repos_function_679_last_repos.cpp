static void ps_list_add(const char *name, const char *cmdline,
                        process_entry_t *entry) {
  procstat_entry_t *pse;

  if (entry->id == 0)
    return;

  for (procstat_t *ps = list_head_g; ps != NULL; ps = ps->next) {
    if ((ps_list_match(name, cmdline, ps)) == 0)
      continue;

#if KERNEL_LINUX
    ps_fill_details(ps, entry);
#endif

    for (pse = ps->instances; pse != NULL; pse = pse->next)
      if ((pse->id == entry->id) || (pse->next == NULL))
        break;

    if ((pse == NULL) || (pse->id != entry->id)) {
      procstat_entry_t *new;

      new = calloc(1, sizeof(*new));
      if (new == NULL)
        return;
      new->id = entry->id;

      if (pse == NULL)
        ps->instances = new;
      else
        pse->next = new;

      pse = new;
    }

    pse->age = 0;

    ps->num_proc += entry->num_proc;
    ps->num_lwp += entry->num_lwp;
    ps->num_fd += entry->num_fd;
    ps->num_maps += entry->num_maps;
    ps->vmem_size += entry->vmem_size;
    ps->vmem_rss += entry->vmem_rss;
    ps->vmem_data += entry->vmem_data;
    ps->vmem_code += entry->vmem_code;
    ps->stack_size += entry->stack_size;

    if ((entry->io_rchar != -1) && (entry->io_wchar != -1)) {
      ps_update_counter(&ps->io_rchar, &pse->io_rchar, entry->io_rchar);
      ps_update_counter(&ps->io_wchar, &pse->io_wchar, entry->io_wchar);
    }

    if ((entry->io_syscr != -1) && (entry->io_syscw != -1)) {
      ps_update_counter(&ps->io_syscr, &pse->io_syscr, entry->io_syscr);
      ps_update_counter(&ps->io_syscw, &pse->io_syscw, entry->io_syscw);
    }

    if ((entry->io_diskr != -1) && (entry->io_diskw != -1)) {
      ps_update_counter(&ps->io_diskr, &pse->io_diskr, entry->io_diskr);
      ps_update_counter(&ps->io_diskw, &pse->io_diskw, entry->io_diskw);
    }

    if ((entry->cswitch_vol != -1) && (entry->cswitch_invol != -1)) {
      ps_update_counter(&ps->cswitch_vol, &pse->cswitch_vol,
                        entry->cswitch_vol);
      ps_update_counter(&ps->cswitch_invol, &pse->cswitch_invol,
                        entry->cswitch_invol);
    }

    ps_update_counter(&ps->vmem_minflt_counter, &pse->vmem_minflt_counter,
                      entry->vmem_minflt_counter);
    ps_update_counter(&ps->vmem_majflt_counter, &pse->vmem_majflt_counter,
                      entry->vmem_majflt_counter);

    ps_update_counter(&ps->cpu_user_counter, &pse->cpu_user_counter,
                      entry->cpu_user_counter);
    ps_update_counter(&ps->cpu_system_counter, &pse->cpu_system_counter,
                      entry->cpu_system_counter);
  }
}