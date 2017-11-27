static void chrony_push_data_valid(const char *p_type, const char *p_type_inst,
                                   const int p_is_valid, double p_value) {
  /* Push real value if p_is_valid is true, push NAN if p_is_valid is not true
   * (idea from ntp plugin) */
  if (p_is_valid == 0)
    p_value = NAN;

  chrony_push_data(p_type, p_type_inst, p_value);
}