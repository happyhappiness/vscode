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