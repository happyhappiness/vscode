const torrent::Object
CommandDownloadSlot::call_list(Command* rawCommand, core::Download* download, const torrent::Object& rawArgs) {
  CommandDownloadSlot* command = static_cast<CommandDownloadSlot*>(rawCommand);

  switch (rawArgs.type()) {
  case torrent::Object::TYPE_LIST:
    return command->m_slot(download, rawArgs);

  case torrent::Object::TYPE_VALUE:
  case torrent::Object::TYPE_STRING:
  {
    torrent::Object tmpList(torrent::Object::TYPE_LIST);
    tmpList.as_list().push_back(rawArgs);

    return command->m_slot(download, tmpList);
  }
  default:
    throw torrent::input_error("Not a list.");
  }
}