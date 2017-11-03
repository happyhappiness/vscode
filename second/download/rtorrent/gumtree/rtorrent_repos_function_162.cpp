const torrent::Object
CommandDownloadSlot::call_unknown(Command* rawCommand, core::Download* download, const torrent::Object& rawArgs) {
  CommandDownloadSlot* command = static_cast<CommandDownloadSlot*>(rawCommand);

  return command->m_slot(download, rawArgs);
}