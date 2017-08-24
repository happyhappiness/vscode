//----------------------------------------------------------------------------
Glob::Glob()
{
  this->Internals = new GlobInternals;
  this->Recurse = false;
  this->Relative = "";
}

//----------------------------------------------------------------------------
Glob::~Glob()
{
  delete this->Internals;
}

//----------------------------------------------------------------------------
void Glob::Escape(int ch, char* buffer)
{
  if (! (
      'a' <= ch && ch <= 'z' ||
      'A' <= ch && ch <= 'Z' ||
      '0' <= ch && ch <= '9') )
    {
    sprintf(buffer, "\\%c", ch);
