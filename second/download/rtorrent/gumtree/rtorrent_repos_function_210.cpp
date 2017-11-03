const torrent::Object
CommandTrackerSlot::call_unknown(Command* rawCommand, torrent::Tracker* tracker, const torrent::Object& rawArgs) {
  CommandTrackerSlot* command = static_cast<CommandTrackerSlot*>(rawCommand);

  return command->m_slot(tracker, rawArgs);
}