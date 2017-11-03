const torrent::Object
CommandFileSlot::call_list(Command* rawCommand, torrent::File* file, const torrent::Object& rawArgs) {
  CommandFileSlot* command = static_cast<CommandFileSlot*>(rawCommand);

  switch (rawArgs.type()) {
  case torrent::Object::TYPE_LIST:
    return command->m_slot(file, rawArgs);

  case torrent::Object::TYPE_VALUE:
  case torrent::Object::TYPE_STRING:
  {
    torrent::Object tmpList(torrent::Object::TYPE_LIST);
    tmpList.as_list().push_back(rawArgs);

    return command->m_slot(file, tmpList);
  }
  default:
    throw torrent::input_error("Not a list.");
  }
}