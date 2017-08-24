(configName != "IMPORTED") {
          if (!tgt->IsImported() &&
              !HandleLocationPropertyPolicy(tgt->GetName(), messenger,
                                            context)) {
            return CM_NULLPTR;
          }
          return ComputeLocation(tgt, configName);
        }