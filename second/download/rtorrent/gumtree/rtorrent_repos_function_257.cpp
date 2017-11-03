const torrent::Object
CommandVariable::set_value(Command* rawCommand, const torrent::Object& rawArgs) {
  CommandVariable* variable = static_cast<CommandVariable*>(rawCommand);

  const torrent::Object& arg = convert_to_single_argument(rawArgs);

  switch (arg.type()) {
  case torrent::Object::TYPE_NONE:
    variable->m_variable = (int64_t)0;
    break;

  case torrent::Object::TYPE_VALUE:
    variable->m_variable = arg;
    break;

  case torrent::Object::TYPE_STRING:
    int64_t value;
    parse_whole_value(arg.as_string().c_str(), &value, 0, 1);

    variable->m_variable = value;
    break;

  default:
    throw torrent::input_error("CommandValue unsupported type restriction.");
  }

  return variable->m_variable;
}