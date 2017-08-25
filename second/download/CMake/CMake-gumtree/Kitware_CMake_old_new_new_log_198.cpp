m::AddError(const char* message, const char* /*unused*/)
{
  this->Errors.push_back(message);
};