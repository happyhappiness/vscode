const torrent::Object
CommandSlot::call_unknown(Command* rawCommand, const torrent::Object& rawArgs) {
  CommandSlot* command = static_cast<CommandSlot*>(rawCommand);

  return command->m_slot(rawArgs);
}