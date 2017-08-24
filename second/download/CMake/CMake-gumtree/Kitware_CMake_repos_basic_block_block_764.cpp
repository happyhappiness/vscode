(!tgt->IsImported() &&
              !HandleLocationPropertyPolicy(tgt->GetName(), messenger,
                                            context)) {
            return CM_NULLPTR;
          }