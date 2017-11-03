void
DownloadList::receive_view_input(Input type) {
  if (control->ui()->current_input() != NULL)
    return;

  input::PathInput* input = new input::PathInput;

  const char* title;

  switch (type) {
  case INPUT_LOAD_DEFAULT:
    title = "load_start";
    break;

  case INPUT_LOAD_MODIFIED:
    title = "load";
    break;

  case INPUT_CHANGE_DIRECTORY:
    title = "change_directory";

    input->str() = rpc::call_command_string("get_directory");
    input->set_pos(input->str().length());

    break;

  case INPUT_COMMAND:
    title = "command";
    break;

  default:
    throw torrent::internal_error("DownloadList::receive_view_input(...) Invalid input type.");
  }

  ElementStringList* esl = dynamic_cast<ElementStringList*>(m_uiArray[DISPLAY_STRING_LIST]);

  input->signal_show_next().connect(sigc::bind(sigc::mem_fun(*this, &DownloadList::activate_display), DISPLAY_STRING_LIST));
  input->signal_show_next().connect(sigc::mem_fun(*esl, &ElementStringList::next_screen));

  input->signal_show_range().connect(sigc::hide(sigc::hide(sigc::bind(sigc::mem_fun(*this, &DownloadList::activate_display), DISPLAY_STRING_LIST))));
  input->signal_show_range().connect(sigc::mem_fun(*esl, &ElementStringList::set_range<utils::Directory::iterator>));

  input->bindings()['\n']      = sigc::bind(sigc::mem_fun(*this, &DownloadList::receive_exit_input), type);
  input->bindings()[KEY_ENTER] = sigc::bind(sigc::mem_fun(*this, &DownloadList::receive_exit_input), type);
  input->bindings()['\x07']    = sigc::bind(sigc::mem_fun(*this, &DownloadList::receive_exit_input), INPUT_NONE);

  control->ui()->enable_input(title, input);
}