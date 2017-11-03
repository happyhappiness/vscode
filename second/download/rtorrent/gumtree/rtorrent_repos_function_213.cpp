const torrent::Object
CommandTrackerSlot::call_string(Command* rawCommand, torrent::Tracker* tracker, const torrent::Object& rawArgs) {
  CommandTrackerSlot* command = static_cast<CommandTrackerSlot*>(rawCommand);

  const torrent::Object& arg = convert_to_single_argument(rawArgs);

  switch (arg.type()) {
  case torrent::Object::TYPE_STRING:
    return command->m_slot(tracker, arg);

//   case torrent::Object::TYPE_NONE:
//     throw torrent::input_error("CDS: void.");

//   case torrent::Object::TYPE_VALUE:
//     throw torrent::input_error("CDS: value.");

//   case torrent::Object::TYPE_LIST:
//     throw torrent::input_error("CDS: list.");

  default:
    throw torrent::input_error("Not a string.");
  }
}