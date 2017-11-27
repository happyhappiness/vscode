static void submit_derive(int cpu_num, int cpu_state, derive_t value) {
  submit_value(cpu_num, cpu_state, "cpu", (value_t){.derive = value});
}