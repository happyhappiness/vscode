void cmCommandArgumentParserHelper::Error(const char* str)
{
  unsigned long pos = static_cast<unsigned long>(this->InputBufferPos);
  cmOStringStream ostr;
  ostr << str << " (" << pos << ")";
  this->ErrorString = ostr.str();
}
