static void submit_derive(int cpu_num, int cpu_state, derive_t derive) {
  value_t value;

  value.derive = derive;
  submit_value(cpu_num, cpu_state, "cpu", value);
}