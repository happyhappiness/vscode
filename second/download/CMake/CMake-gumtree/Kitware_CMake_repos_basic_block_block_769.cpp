(cmHasLiteralPrefix(prop, "LOCATION_")) {
        if (!tgt->IsImported() &&
            !HandleLocationPropertyPolicy(tgt->GetName(), messenger,
                                          context)) {
          return CM_NULLPTR;
        }
        const char* configName = prop.c_str() + 9;
        return ComputeLocation(tgt, configName);
      }