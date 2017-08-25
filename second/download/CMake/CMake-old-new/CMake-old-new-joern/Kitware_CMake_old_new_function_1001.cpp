void cmCursesMainForm::UpdateCurrentEntry()
{
  FIELD* cur = current_field(m_Form);
  int index = field_index(cur);
  char* text = field_buffer(m_Fields[index-2], 0);

  int x,y;
  getmaxyx(m_Window, y, x);
  move(y-1,0);
  printw(text);

  char version[128];
  sprintf(version,"CMake Version %d.%d", cmMakefile::GetMajorVersion(),
	  cmMakefile::GetMinorVersion());
  int len = strlen(version);
  move(y-1, x-len);
  printw(version);

  pos_form_cursor(m_Form);
}