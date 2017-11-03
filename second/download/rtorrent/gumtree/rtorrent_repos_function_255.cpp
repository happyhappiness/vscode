const torrent::Object
CommandVariable::set_bool(Command* rawCommand, const torrent::Object& rawArgs) {
  CommandVariable* variable = static_cast<CommandVariable*>(rawCommand);

  const torrent::Object& arg = convert_to_single_argument(rawArgs);

  switch (arg.type()) {
  case torrent::Object::TYPE_VALUE:
    variable->m_variable = arg.as_value() ? (int64_t)1 : (int64_t)0;
    break;

  case torrent::Object::TYPE_STRING:
    // Move the checks into some is_true, is_false think in Command.
    if (arg.as_string() == "yes" || arg.as_string() == "true")
      variable->m_variable = (int64_t)1;

    else if (arg.as_string() == "no" || arg.as_string() == "false")
      variable->m_variable = (int64_t)0;

    else
      throw torrent::input_error("String does not parse as a boolean.");

    break;

  default:
    throw torrent::input_error("Input is not a boolean.");
  }

  return variable->m_variable;
}