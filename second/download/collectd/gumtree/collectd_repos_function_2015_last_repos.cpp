void module_register(void) {
  plugin_register_init(PMU_PLUGIN, pmu_init);
  plugin_register_complex_config(PMU_PLUGIN, pmu_config);
  plugin_register_complex_read(NULL, PMU_PLUGIN, pmu_read, 0, NULL);
  plugin_register_shutdown(PMU_PLUGIN, pmu_shutdown);
}