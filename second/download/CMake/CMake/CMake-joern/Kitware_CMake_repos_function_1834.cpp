void CMakeMessageHandler(const char* message, const char* title,
                         bool& /*unused*/, void* clientData)
{
  cmCursesForm* self = static_cast<cmCursesForm*>(clientData);
  self->AddError(message, title);
}