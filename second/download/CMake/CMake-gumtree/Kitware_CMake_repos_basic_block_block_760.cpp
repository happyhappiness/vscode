{
    if (const char* loc = GetLocation(tgt, prop, messenger, context)) {
      return loc;
    }
    if (cmSystemTools::GetFatalErrorOccured()) {
      return CM_NULLPTR;
    }
    if (prop == "SOURCES") {
      return GetSources(tgt, messenger, context);
    }
    return CM_NULLPTR;
  }