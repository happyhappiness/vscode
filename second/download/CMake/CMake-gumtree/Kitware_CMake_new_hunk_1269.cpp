    return (res != 0);
    }
#endif
  if ( m_RegistryType == Registry::FILE_REGISTRY )
    {
    kwsys_stl::string key = this->CreateKey( skey );
    if ( key.empty() )
      {
      return 0;
      }
    this->EntriesMap[key] = this->EncodeValue(value);
    return 1;
    }
  return false;
}

//----------------------------------------------------------------------------
kwsys_stl::string RegistryHelper::CreateKey( const char *key )
{
  if ( !m_SubKeySpecified || m_SubKey.empty() || !key )
    {
    return "";
    }
  kwsys_ios::ostringstream ostr;
  ostr << this->EncodeKey(this->m_SubKey.c_str()) << "\\" << this->EncodeKey(key);
  return ostr.str();
}

//----------------------------------------------------------------------------
void RegistryHelper::SetSubKey(const char* sk)
{
  if ( !sk )
