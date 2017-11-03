torrent::Object
apply_load(int flags, const torrent::Object& rawArgs) {
  const torrent::Object::list_type&          args    = rawArgs.as_list();
  torrent::Object::list_type::const_iterator argsItr = args.begin();

  if (argsItr == args.end())
    throw torrent::input_error("Too few arguments.");

  const std::string& filename = argsItr->as_string();
  core::Manager::command_list_type commands;

  while (++argsItr != args.end())
    commands.push_back(argsItr->as_string());

  control->core()->try_create_download_expand(filename, flags, commands);

  return torrent::Object();
}