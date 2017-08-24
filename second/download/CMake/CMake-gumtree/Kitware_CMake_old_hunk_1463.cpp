  FIELD* cur = current_field(m_Form);
  int index = field_index(cur);
  cmCursesWidget* lbl = reinterpret_cast<cmCursesWidget*>(field_userptr(
    m_Fields[index-2]));
  const char* curField = lbl->GetValue();

  // Get the help string of the current entry
  // and add it to the help string
  char help[128];
  cmCacheManager::CacheIterator it = 
    this->m_CMakeInstance->GetCacheManager()->GetCacheIterator(curField);
  if (!it.IsAtEnd())
    {
    const char* hs = it.GetProperty("HELPSTRING");
    if ( hs )
      {
      strncpy(help, hs, 127);
      help[127] = '\0';
      }
    else
      {
      help[0] = 0;
      }
    }
  else
    {
    sprintf(help," ");
    }


  // Join the key, help string and pad with spaces
  // (or truncate) as necessary
