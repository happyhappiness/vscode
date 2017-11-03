const torrent::Object
CommandPeerSlot::call_string(Command* rawCommand, torrent::Peer* peer, const torrent::Object& rawArgs) {
  CommandPeerSlot* command = static_cast<CommandPeerSlot*>(rawCommand);

  const torrent::Object& arg = convert_to_single_argument(rawArgs);

  switch (arg.type()) {
  case torrent::Object::TYPE_STRING:
    return command->m_slot(peer, arg);

//   case torrent::Object::TYPE_NONE:
//     throw torrent::input_error("CDS: void.");

//   case torrent::Object::TYPE_VALUE:
//     throw torrent::input_error("CDS: value.");

//   case torrent::Object::TYPE_LIST:
//     throw torrent::input_error("CDS: list.");

  default:
    throw torrent::input_error("Not a string.");
  }
}