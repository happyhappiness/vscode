const torrent::Object
CommandSlot::call_list(Command* rawCommand, const torrent::Object& rawArgs) {
  CommandSlot* command = static_cast<CommandSlot*>(rawCommand);

  switch (rawArgs.type()) {
  case torrent::Object::TYPE_LIST:
    return command->m_slot(rawArgs);

  case torrent::Object::TYPE_VALUE:
  case torrent::Object::TYPE_STRING:
  {
    torrent::Object tmpList(torrent::Object::TYPE_LIST);
    tmpList.as_list().push_back(rawArgs);

    return command->m_slot(tmpList);
  }
  default:
    throw torrent::input_error("Not a list.");
  }
}