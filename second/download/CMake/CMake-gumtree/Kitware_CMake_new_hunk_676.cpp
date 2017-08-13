      {
      char indexString[32];
      sprintf(indexString, "%d", index);
      this->Makefile->AddDefinition(variableName, indexString);
      return true;
      }
    index++;
    }

  this->Makefile->AddDefinition(variableName, "-1");
  return true;
}

