m::AddError(const char* message, const char* title)
{
  m_Errors.push_back(message);
}

void cmCursesMainForm::RemoveEntry(const char* value)
{
  if (!value)
    {
    return;
    }

  std::vector<cmCursesCacheEntryComposite*>::iterator it;