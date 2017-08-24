{
    int ch = expr[cc];
    if (ch == '/') {
      if (!cexpr.empty()) {
        this->AddExpression(cexpr);
      }
      cexpr = "";
    } else {
      cexpr.append(1, static_cast<char>(ch));
    }
  }