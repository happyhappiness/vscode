void
initialize_commands() {
  initialize_command_events();
  initialize_command_network();
  initialize_command_local();
  initialize_command_ui();
  initialize_command_download();
  initialize_command_file();
  initialize_command_peer();
  initialize_command_tracker();

#ifdef ADDING_COMMANDS 
  if (commandSlotsItr > commandSlots + COMMAND_SLOTS_SIZE ||
      commandVariablesItr > commandVariables + COMMAND_VARIABLES_SIZE ||
      commandDownloadSlotsItr > commandDownloadSlots + COMMAND_DOWNLOAD_SLOTS_SIZE ||
      commandFileSlotsItr > commandFileSlots + COMMAND_FILE_SLOTS_SIZE ||
      commandPeerSlotsItr > commandPeerSlots + COMMAND_PEER_SLOTS_SIZE ||
      commandTrackerSlotsItr > commandTrackerSlots + COMMAND_TRACKER_SLOTS_SIZE)
#else
  if (commandSlotsItr != commandSlots + COMMAND_SLOTS_SIZE ||
      commandVariablesItr != commandVariables + COMMAND_VARIABLES_SIZE ||
      commandDownloadSlotsItr != commandDownloadSlots + COMMAND_DOWNLOAD_SLOTS_SIZE ||
      commandFileSlotsItr != commandFileSlots + COMMAND_FILE_SLOTS_SIZE ||
      commandPeerSlotsItr != commandPeerSlots + COMMAND_PEER_SLOTS_SIZE ||
      commandTrackerSlotsItr != commandTrackerSlots + COMMAND_TRACKER_SLOTS_SIZE)
#endif
    throw torrent::internal_error("initialize_commands() static command array size mismatch.");
}