      {
      char indexString[32];
      sprintf(indexString, "%d", index);
      this->Makefile->AddDefinition(variableName.c_str(), indexString);
      return true;
      }
    index++;
    }

  this->Makefile->AddDefinition(variableName.c_str(), "-1");
  return true;
}

