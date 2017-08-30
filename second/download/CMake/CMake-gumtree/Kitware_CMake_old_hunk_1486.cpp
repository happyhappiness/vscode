  char buffer[1024];
  sprintf(buffer, "%d", static_cast<int>(length));

  m_Makefile->AddDefinition(variableName.c_str(), buffer);
  return true;
}

