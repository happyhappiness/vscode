int
parse_options(Control* c, int argc, char** argv) {
  try {
    OptionParser optionParser;

    // Converted.
    optionParser.insert_flag('h', sigc::ptr_fun(&print_help));
    optionParser.insert_flag('n', OptionParser::Slot());

    optionParser.insert_option('b', sigc::bind<0>(sigc::ptr_fun(&rpc::call_command_set_string), "bind"));
    optionParser.insert_option('d', sigc::bind<0>(sigc::ptr_fun(&rpc::call_command_set_string), "directory"));
    optionParser.insert_option('i', sigc::bind<0>(sigc::ptr_fun(&rpc::call_command_set_string), "ip"));
    optionParser.insert_option('p', sigc::bind<0>(sigc::ptr_fun(&rpc::call_command_set_string), "port_range"));
    optionParser.insert_option('s', sigc::bind<0>(sigc::ptr_fun(&rpc::call_command_set_string), "session"));

    optionParser.insert_option('O', sigc::ptr_fun(&rpc::parse_command_single_std));
    optionParser.insert_option_list('o', sigc::ptr_fun(&rpc::call_command_set_std_string));

    return optionParser.process(argc, argv);

  } catch (torrent::input_error& e) {
    throw torrent::input_error("Failed to parse command line option: " + std::string(e.what()));
  }
}