const torrent::Object
CommandVariable::set_string(Command* rawCommand, const torrent::Object& rawArgs) {
  CommandVariable* variable = static_cast<CommandVariable*>(rawCommand);

  const torrent::Object& arg = convert_to_single_argument(rawArgs);

  switch (arg.type()) {
  case torrent::Object::TYPE_NONE:
    variable->m_variable = std::string("");
    break;

//   case torrent::Object::TYPE_VALUE:
//     variable->m_variable = arg;
//     break;

  case torrent::Object::TYPE_STRING:
    variable->m_variable = arg;
    break;

  default:
    throw torrent::input_error("Not a string.");
  }

  return variable->m_variable;
}