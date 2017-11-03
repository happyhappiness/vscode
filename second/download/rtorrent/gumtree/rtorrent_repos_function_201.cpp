const torrent::Object
CommandFileSlot::call_unknown(Command* rawCommand, torrent::File* file, const torrent::Object& rawArgs) {
  CommandFileSlot* command = static_cast<CommandFileSlot*>(rawCommand);

  return command->m_slot(file, rawArgs);
}