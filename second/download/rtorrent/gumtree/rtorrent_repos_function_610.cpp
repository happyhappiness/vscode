inline TextElementValueBase*
te_variable_value(const char* variable, int flags = TextElementValueBase::flag_normal, int attributes = Attributes::a_invalid) {
  return text_element_value_slot(rak::bind1st(std::ptr_fun(&rpc::call_command_d_value), variable), flags, attributes);
}