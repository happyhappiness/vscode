const torrent::Object
CommandPeerSlot::call_list(Command* rawCommand, torrent::Peer* peer, const torrent::Object& rawArgs) {
  CommandPeerSlot* command = static_cast<CommandPeerSlot*>(rawCommand);

  switch (rawArgs.type()) {
  case torrent::Object::TYPE_LIST:
    return command->m_slot(peer, rawArgs);

  case torrent::Object::TYPE_VALUE:
  case torrent::Object::TYPE_STRING:
  {
    torrent::Object tmpList(torrent::Object::TYPE_LIST);
    tmpList.as_list().push_back(rawArgs);

    return command->m_slot(peer, tmpList);
  }
  default:
    throw torrent::input_error("Not a list.");
  }
}