void
add_variable(const char* getKey, const char* setKey, const char* defaultSetKey,
             rpc::CommandMap::generic_slot getSlot, rpc::CommandMap::generic_slot setSlot,
             const torrent::Object& defaultObject) {
  rpc::CommandVariable* variable = commandVariablesItr++;
  variable->set_variable(defaultObject);

  rpc::commands.insert_generic(getKey, variable, getSlot, rpc::CommandMap::flag_dont_delete | rpc::CommandMap::flag_public_xmlrpc, "i:", "");

  if (setKey)
    rpc::commands.insert_generic(setKey, variable, setSlot, rpc::CommandMap::flag_dont_delete | rpc::CommandMap::flag_public_xmlrpc, "i:", "");

  if (defaultSetKey)
    rpc::commands.insert_generic(defaultSetKey, variable, setSlot, rpc::CommandMap::flag_dont_delete, "i:", "");
}