const torrent::Object
CommandPeerSlot::call_unknown(Command* rawCommand, torrent::Peer* peer, const torrent::Object& rawArgs) {
  CommandPeerSlot* command = static_cast<CommandPeerSlot*>(rawCommand);

  return command->m_slot(peer, rawArgs);
}