const torrent::Object
CommandSlot::call_string(Command* rawCommand, const torrent::Object& rawArgs) {
  CommandSlot* command = static_cast<CommandSlot*>(rawCommand);

  const torrent::Object& arg = convert_to_single_argument(rawArgs);

  switch (arg.type()) {
//   case torrent::Object::TYPE_VALUE:
//     break;

  case torrent::Object::TYPE_STRING:
    return command->m_slot(arg);
    break;

  default:
    throw torrent::input_error("Not a string.");
  }
}