static int ssl_ui_reader(UI *ui, UI_STRING *uis)
{
  const char *password;
  switch(UI_get_string_type(uis)) {
  case UIT_PROMPT:
  case UIT_VERIFY:
    password = (const char *)UI_get0_user_data(ui);
    if(password && (UI_get_input_flags(uis) & UI_INPUT_FLAG_DEFAULT_PWD)) {
      UI_set_result(ui, uis, password);
      return 1;
    }
  default:
    break;
  }
  return (UI_method_get_reader(UI_OpenSSL()))(ui, uis);
}