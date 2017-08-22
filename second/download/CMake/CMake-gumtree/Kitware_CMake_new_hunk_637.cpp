  // do not check the return value here
  // if the list var is not found varArgsExpanded will have size 0
  // and we will return 0
  this->GetList(varArgsExpanded, listName);
  size_t length = varArgsExpanded.size();
  char buffer[1024];
  sprintf(buffer, "%d", static_cast<int>(length));

  this->Makefile->AddDefinition(variableName, buffer);
  return true;
}

