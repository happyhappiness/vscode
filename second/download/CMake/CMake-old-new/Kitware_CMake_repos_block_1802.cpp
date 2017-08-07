{
  cmCursesForm* self = static_cast<cmCursesForm*>(clientData);
  self->AddError(message, title);
}