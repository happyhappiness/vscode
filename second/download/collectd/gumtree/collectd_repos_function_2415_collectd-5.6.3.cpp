int check_capability(int arg) /* {{{ */
{
  cap_value_t cap_value = (cap_value_t)arg;
  cap_t cap;
  cap_flag_value_t cap_flag_value;

  if (!CAP_IS_SUPPORTED(cap_value))
    return (-1);

  if (!(cap = cap_get_proc())) {
    ERROR("check_capability: cap_get_proc failed.");
    return (-1);
  }

  if (cap_get_flag(cap, cap_value, CAP_EFFECTIVE, &cap_flag_value) < 0) {
    ERROR("check_capability: cap_get_flag failed.");
    cap_free(cap);
    return (-1);
  }
  cap_free(cap);

  return (cap_flag_value != CAP_SET);
}