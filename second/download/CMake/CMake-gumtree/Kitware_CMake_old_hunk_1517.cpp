  m_ShowAdvanced = false;
}

  
void cmakewizard::AskUser(const char* key, cmCacheManager::CacheIterator& iter)
{
  printf("Variable Name: %s\n", key);
  const char* helpstring = iter.GetProperty("HELPSTRING");
