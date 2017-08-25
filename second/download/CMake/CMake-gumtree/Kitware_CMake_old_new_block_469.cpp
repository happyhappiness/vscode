{
      int dependee_index = *ni;
      cmTarget const* dependee = this->Targets[dependee_index];
      fprintf(stderr, "  depends on target %d [%s] (%s)\n", dependee_index,
              dependee->GetName(), ni->IsStrong()? "strong" : "weak");
      }