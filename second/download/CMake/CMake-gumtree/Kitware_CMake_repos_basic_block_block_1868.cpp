{
    SymbolProperties symProps;
    symProps.SetReportPath(wholePath);
    symProps.Initialize(stackSymbols[i]);
    oss << symProps << std::endl;
  }