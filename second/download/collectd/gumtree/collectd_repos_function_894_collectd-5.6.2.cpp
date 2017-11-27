static int submit_counters(struct thread_data *t, struct core_data *c,
                           struct pkg_data *p) {
  char name[DATA_MAX_NAME_LEN];
  double interval_float;

  interval_float = CDTIME_T_TO_DOUBLE(time_delta);

  ssnprintf(name, sizeof(name), "cpu%02d", t->cpu_id);

  if (!aperf_mperf_unstable)
    turbostat_submit(name, "percent", "c0", 100.0 * t->mperf / t->tsc);
  if (!aperf_mperf_unstable)
    turbostat_submit(name, "percent", "c1", 100.0 * t->c1 / t->tsc);

  turbostat_submit(name, "frequency", "average",
                   1.0 / 1000000 * t->aperf / interval_float);

  if ((!aperf_mperf_unstable) || (!(t->aperf > t->tsc || t->mperf > t->tsc)))
    turbostat_submit(name, "frequency", "busy", 1.0 * t->tsc / 1000000 *
                                                    t->aperf / t->mperf /
                                                    interval_float);

  /* Sanity check (should stay stable) */
  turbostat_submit(name, "gauge", "TSC",
                   1.0 * t->tsc / 1000000 / interval_float);

  /* SMI */
  if (do_smi)
    turbostat_submit(name, "count", NULL, t->smi_count);

  /* submit per-core data only for 1st thread in core */
  if (!(t->flags & CPU_IS_FIRST_THREAD_IN_CORE))
    goto done;

  ssnprintf(name, sizeof(name), "core%02d", c->core_id);

  if (do_core_cstate & (1 << 3))
    turbostat_submit(name, "percent", "c3", 100.0 * c->c3 / t->tsc);
  if (do_core_cstate & (1 << 6))
    turbostat_submit(name, "percent", "c6", 100.0 * c->c6 / t->tsc);
  if (do_core_cstate & (1 << 7))
    turbostat_submit(name, "percent", "c7", 100.0 * c->c7 / t->tsc);

  if (do_dts)
    turbostat_submit(name, "temperature", NULL, c->core_temp_c);

  /* submit per-package data only for 1st core in package */
  if (!(t->flags & CPU_IS_FIRST_CORE_IN_PACKAGE))
    goto done;

  ssnprintf(name, sizeof(name), "pkg%02d", p->package_id);

  if (do_ptm)
    turbostat_submit(name, "temperature", NULL, p->pkg_temp_c);

  if (do_pkg_cstate & (1 << 2))
    turbostat_submit(name, "percent", "pc2", 100.0 * p->pc2 / t->tsc);
  if (do_pkg_cstate & (1 << 3))
    turbostat_submit(name, "percent", "pc3", 100.0 * p->pc3 / t->tsc);
  if (do_pkg_cstate & (1 << 6))
    turbostat_submit(name, "percent", "pc6", 100.0 * p->pc6 / t->tsc);
  if (do_pkg_cstate & (1 << 7))
    turbostat_submit(name, "percent", "pc7", 100.0 * p->pc7 / t->tsc);
  if (do_pkg_cstate & (1 << 8))
    turbostat_submit(name, "percent", "pc8", 100.0 * p->pc8 / t->tsc);
  if (do_pkg_cstate & (1 << 9))
    turbostat_submit(name, "percent", "pc9", 100.0 * p->pc9 / t->tsc);
  if (do_pkg_cstate & (1 << 10))
    turbostat_submit(name, "percent", "pc10", 100.0 * p->pc10 / t->tsc);

  if (do_rapl) {
    if (do_rapl & RAPL_PKG)
      turbostat_submit(name, "power", "pkg",
                       p->energy_pkg * rapl_energy_units / interval_float);
    if (do_rapl & RAPL_CORES)
      turbostat_submit(name, "power", "cores",
                       p->energy_cores * rapl_energy_units / interval_float);
    if (do_rapl & RAPL_GFX)
      turbostat_submit(name, "power", "GFX",
                       p->energy_gfx * rapl_energy_units / interval_float);
    if (do_rapl & RAPL_DRAM)
      turbostat_submit(name, "power", "DRAM",
                       p->energy_dram * rapl_energy_units / interval_float);
  }
done:
  return 0;
}