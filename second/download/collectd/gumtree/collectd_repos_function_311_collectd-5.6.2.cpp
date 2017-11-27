static void cpu_reset(void) /* {{{ */
{
  for (size_t i = 0; i < cpu_states_num; i++)
    cpu_states[i].has_value = 0;

  global_cpu_num = 0;
}