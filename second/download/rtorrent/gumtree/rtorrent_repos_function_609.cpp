inline TextElementStringBase*
te_variable_string(const char* variable, int flags = TextElementStringBase::flag_normal, int attributes = Attributes::a_invalid) {
  return text_element_string_slot(rak::bind1st(std::ptr_fun(&rpc::call_command_d_string), variable), flags, attributes);
}