static inline void delta_package(struct pkg_data *delta,
                                 const struct pkg_data *new,
                                 const struct pkg_data *old) {
  delta->pc2 = new->pc2 - old->pc2;
  delta->pc3 = new->pc3 - old->pc3;
  delta->pc6 = new->pc6 - old->pc6;
  delta->pc7 = new->pc7 - old->pc7;
  delta->pc8 = new->pc8 - old->pc8;
  delta->pc9 = new->pc9 - old->pc9;
  delta->pc10 = new->pc10 - old->pc10;
  delta->pkg_temp_c = new->pkg_temp_c;

  delta->energy_pkg = new->energy_pkg - old->energy_pkg;
  delta->energy_cores = new->energy_cores - old->energy_cores;
  delta->energy_gfx = new->energy_gfx - old->energy_gfx;
  delta->energy_dram = new->energy_dram - old->energy_dram;
}