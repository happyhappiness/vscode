    return (res != 0);
    }
#endif
  if ( m_RegistryType == Registry::UNIX_REGISTRY )
    {
    char *key = this->CreateKey( skey );
    if ( !key )
      {
      return 0;
      }
    this->EntriesMap[key] = value;
    delete [] key;
    return 1;
    }
  return false;
}

//----------------------------------------------------------------------------
char *RegistryHelper::CreateKey( const char *key )
{
  char *newkey;
  if ( !m_SubKeySpecified || m_SubKey.empty() || !key )
    {
    return 0;
    }
  int len = strlen(this->m_SubKey.c_str()) + strlen(key) + 1;
  newkey = new char[ len+1 ] ;
  ::sprintf(newkey, "%s\\%s", this->m_SubKey.c_str(), key);
  return newkey;
}

void RegistryHelper::SetSubKey(const char* sk)
{
  if ( !sk )
