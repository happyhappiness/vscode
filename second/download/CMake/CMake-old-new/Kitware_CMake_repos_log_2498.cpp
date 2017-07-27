fprintf(stderr, "  depends on target %d [%s] (%s)\n", dependee_index,
              dependee->GetName().c_str(), ni->IsStrong() ? "strong" : "weak")