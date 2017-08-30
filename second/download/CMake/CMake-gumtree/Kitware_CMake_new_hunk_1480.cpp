
void cmCursesMainForm::AddError(const char* message, const char*)
{
  this->Errors.push_back(message);
}

void cmCursesMainForm::RemoveEntry(const char* value)
