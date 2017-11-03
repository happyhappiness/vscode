void
initialize_command_ui() {
  ADD_VARIABLE_STRING("key_layout", "qwerty");

  ADD_COMMAND_STRING("view_add",        rpc::object_string_fn(rak::make_mem_fun(control->view_manager(), &core::ViewManager::insert_throw)));
  ADD_COMMAND_NONE_L("view_list",       rak::ptr_fn(&apply_view_list));

  ADD_COMMAND_LIST("view_filter",       rak::bind_ptr_fn(&apply_view_filter, &core::ViewManager::set_filter));
  ADD_COMMAND_LIST("view_filter_on",    rak::bind_ptr_fn(&apply_view_filter, &core::ViewManager::set_filter_on));

  ADD_COMMAND_LIST("view_sort",         rak::ptr_fn(&apply_view_sort));
  ADD_COMMAND_LIST("view_sort_new",     rak::bind_ptr_fn(&apply_view_filter, &core::ViewManager::set_sort_new));
  ADD_COMMAND_LIST("view_sort_current", rak::bind_ptr_fn(&apply_view_filter, &core::ViewManager::set_sort_current));

//   ADD_COMMAND_LIST("view_sort_current", rak::bind_ptr_fn(&apply_view_filter, &core::ViewManager::set_sort_current));

  ADD_COMMAND_LIST("print",             rak::ptr_fn(&apply_print));
}