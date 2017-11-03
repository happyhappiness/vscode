const torrent::Object
CommandDownloadSlot::call_string(Command* rawCommand, core::Download* download, const torrent::Object& rawArgs) {
  CommandDownloadSlot* command = static_cast<CommandDownloadSlot*>(rawCommand);

  const torrent::Object& arg = convert_to_single_argument(rawArgs);

  switch (arg.type()) {
  case torrent::Object::TYPE_STRING:
    return command->m_slot(download, arg);

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