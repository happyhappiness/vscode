  return m_GlobalScope;
}

//----------------------------------------------------------------------------
kwsys_stl::string RegistryHelper::EncodeKey(const char* str)
{
  kwsys_ios::ostringstream ostr;
  while ( *str )
    {
    switch ( *str )
      {
    case '%': case '=': case '\n': case '\r': case '\t': case ' ':
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

//----------------------------------------------------------------------------
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

//----------------------------------------------------------------------------
kwsys_stl::string RegistryHelper::DecodeValue(const char* str)
{
  kwsys_ios::ostringstream ostr;
  while ( *str )
    {
    int val;
    switch ( *str )
      {
    case '%':
      if ( *(str+1) && *(str+2) && sscanf(str+1, "%x", &val) == 1 )
        {
        ostr << (char)val;
        str += 2;
        }
      else
        {
        ostr << *str;
        }
      break;
    default:
      ostr << *str;
      }
    str ++;
    }
  return ostr.str();
}

} // namespace KWSYS_NAMESPACE