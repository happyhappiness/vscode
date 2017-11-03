const torrent::Object
CommandVariable::get_bool(Command* rawCommand, const torrent::Object& args) {
  CommandVariable* variable = static_cast<CommandVariable*>(rawCommand);

  return variable->m_variable;
}