{
      static const std::string propLOCATION = "LOCATION";
      if (prop == propLOCATION) {
        if (!tgt->IsImported() &&
            !HandleLocationPropertyPolicy(tgt->GetName(), messenger,
                                          context)) {
          return CM_NULLPTR;
        }
        return ComputeLocationForBuild(tgt);
      }

      // Support "LOCATION_<CONFIG>".
      if (cmHasLiteralPrefix(prop, "LOCATION_")) {
        if (!tgt->IsImported() &&
            !HandleLocationPropertyPolicy(tgt->GetName(), messenger,
                                          context)) {
          return CM_NULLPTR;
        }
        const char* configName = prop.c_str() + 9;
        return ComputeLocation(tgt, configName);
      }

      // Support "<CONFIG>_LOCATION".
      if (cmHasLiteralSuffix(prop, "_LOCATION") &&
          !cmHasLiteralPrefix(prop, "XCODE_ATTRIBUTE_")) {
        std::string configName(prop.c_str(), prop.size() - 9);
        if (configName != "IMPORTED") {
          if (!tgt->IsImported() &&
              !HandleLocationPropertyPolicy(tgt->GetName(), messenger,
                                            context)) {
            return CM_NULLPTR;
          }
          return ComputeLocation(tgt, configName);
        }
      }
    }