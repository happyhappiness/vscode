kwsys_stl::string RegistryHelper::EncodeValue(const char* str)
{
  kwsys_ios::ostringstream ostr;
  while ( *str )
    {
    switch ( *str )
      {
    case '%': case '=': case '\n': case '\r': case '\t': 
      char buffer[4];
      sprintf(buffer, "%%%02X", *str);
      ostr << buffer;
      break;
    default:
      ostr << *str;
      }
    str ++;
    }
  return ostr.str();
}