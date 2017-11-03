const torrent::Object
CommandTrackerSlot::call_list(Command* rawCommand, torrent::Tracker* tracker, const torrent::Object& rawArgs) {
  CommandTrackerSlot* command = static_cast<CommandTrackerSlot*>(rawCommand);

  switch (rawArgs.type()) {
  case torrent::Object::TYPE_LIST:
    return command->m_slot(tracker, rawArgs);

  case torrent::Object::TYPE_VALUE:
  case torrent::Object::TYPE_STRING:
  {
    torrent::Object tmpList(torrent::Object::TYPE_LIST);
    tmpList.as_list().push_back(rawArgs);

    return command->m_slot(tracker, tmpList);
  }
  default:
    throw torrent::input_error("Not a list.");
  }
}