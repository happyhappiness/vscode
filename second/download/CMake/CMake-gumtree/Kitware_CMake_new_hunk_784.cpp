      {
      int i = *ni;
      fprintf(stderr, "  contains target %d [%s]\n",
              i, this->Targets[i]->GetName().c_str());
      }
    }
  fprintf(stderr, "\n");