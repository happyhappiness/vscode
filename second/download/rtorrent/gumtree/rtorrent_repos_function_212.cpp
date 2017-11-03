const torrent::Object
CommandTrackerSlot::call_value_base(Command* rawCommand, torrent::Tracker* tracker, const torrent::Object& rawArgs, int base, int unit) {
  CommandTrackerSlot* command = static_cast<CommandTrackerSlot*>(rawCommand);

  const torrent::Object& arg = convert_to_single_argument(rawArgs);

  switch (arg.type()) {
  case torrent::Object::TYPE_VALUE:
    // Should shift this one too, so it gives the right unit.
    return command->m_slot(tracker, arg);

  case torrent::Object::TYPE_STRING:
  {
    torrent::Object argValue(torrent::Object::TYPE_VALUE);

    if (!parse_whole_value_nothrow(arg.as_string().c_str(), &argValue.as_value(), base, unit))
      throw torrent::input_error("Not a value.");

    return command->m_slot(tracker, argValue);
  }
  default:
    throw torrent::input_error("Not a value.");
  }
}