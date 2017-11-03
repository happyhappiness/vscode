torrent::Object
apply_view_filter(view_filter_slot viewFilterSlot, const torrent::Object& rawArgs) {
  const torrent::Object::list_type& args = rawArgs.as_list();

  if (args.size() < 1)
    throw torrent::input_error("Too few arguments.");

  const std::string& name = args.front().as_string();
  
  if (name.empty())
    throw torrent::input_error("First argument must be a string.");

  core::ViewManager::filter_args filterArgs;

  for (torrent::Object::list_type::const_iterator itr = ++args.begin(), last = args.end(); itr != last; itr++)
    filterArgs.push_back(itr->as_string());

  (control->view_manager()->*viewFilterSlot)(name, filterArgs);

  return torrent::Object();
}