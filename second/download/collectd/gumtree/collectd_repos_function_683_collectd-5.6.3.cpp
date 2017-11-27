static void ps_list_add(const char *name, const char *cmdline,
                        procstat_entry_t *entry) {
  procstat_entry_t *pse;

  if (entry->id == 0)
    return;

  for (procstat_t *ps = list_head_g; ps != NULL; ps = ps->next) {
    _Bool want_init;

    if ((ps_list_match(name, cmdline, ps)) == 0)
      continue;

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
    pse->num_proc = entry->num_proc;
    pse->num_lwp = entry->num_lwp;
    pse->vmem_size = entry->vmem_size;
    pse->vmem_rss = entry->vmem_rss;
    pse->vmem_data = entry->vmem_data;
    pse->vmem_code = entry->vmem_code;
    pse->stack_size = entry->stack_size;
    pse->io_rchar = entry->io_rchar;
    pse->io_wchar = entry->io_wchar;
    pse->io_syscr = entry->io_syscr;
    pse->io_syscw = entry->io_syscw;
    pse->cswitch_vol = entry->cswitch_vol;
    pse->cswitch_invol = entry->cswitch_invol;

    ps->num_proc += pse->num_proc;
    ps->num_lwp += pse->num_lwp;
    ps->vmem_size += pse->vmem_size;
    ps->vmem_rss += pse->vmem_rss;
    ps->vmem_data += pse->vmem_data;
    ps->vmem_code += pse->vmem_code;
    ps->stack_size += pse->stack_size;

    ps->io_rchar += ((pse->io_rchar == -1) ? 0 : pse->io_rchar);
    ps->io_wchar += ((pse->io_wchar == -1) ? 0 : pse->io_wchar);
    ps->io_syscr += ((pse->io_syscr == -1) ? 0 : pse->io_syscr);
    ps->io_syscw += ((pse->io_syscw == -1) ? 0 : pse->io_syscw);

    ps->cswitch_vol += ((pse->cswitch_vol == -1) ? 0 : pse->cswitch_vol);
    ps->cswitch_invol += ((pse->cswitch_invol == -1) ? 0 : pse->cswitch_invol);

    want_init =
        (entry->vmem_minflt_counter == 0) && (entry->vmem_majflt_counter == 0);
    ps_update_counter(want_init, &ps->vmem_minflt_counter,
                      &pse->vmem_minflt_counter, &pse->vmem_minflt,
                      entry->vmem_minflt_counter, entry->vmem_minflt);
    ps_update_counter(want_init, &ps->vmem_majflt_counter,
                      &pse->vmem_majflt_counter, &pse->vmem_majflt,
                      entry->vmem_majflt_counter, entry->vmem_majflt);

    want_init =
        (entry->cpu_user_counter == 0) && (entry->cpu_system_counter == 0);
    ps_update_counter(want_init, &ps->cpu_user_counter, &pse->cpu_user_counter,
                      &pse->cpu_user, entry->cpu_user_counter, entry->cpu_user);
    ps_update_counter(want_init, &ps->cpu_system_counter,
                      &pse->cpu_system_counter, &pse->cpu_system,
                      entry->cpu_system_counter, entry->cpu_system);
  }
}