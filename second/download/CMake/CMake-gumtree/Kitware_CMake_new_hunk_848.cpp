  char buffer[1024];

  sprintf(buffer, "%d", static_cast<int>(length));



  this->Makefile->AddDefinition(variableName, buffer);

  return true;

}



