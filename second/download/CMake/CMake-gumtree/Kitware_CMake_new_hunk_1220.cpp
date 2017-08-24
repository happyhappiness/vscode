void cmCommandArgumentParserHelper::Error(const char* str)
{
  unsigned long pos = static_cast<unsigned long>(this->InputBufferPos);
  //fprintf(stderr, "Argument Parser Error: %s (%lu / Line: %d)\n", str, pos, this->CurrentLine);
  cmOStringStream ostr;
  ostr << str << " (" << pos << ")";
  /*
  int cc;
  std::cerr << "String: [";
  for ( cc = 0; cc < 30 && *(this->InputBuffer.c_str() + this->InputBufferPos + cc);
