bool Reader::expectToken(TokenType type, Token& token, const char* message) {
  readToken(token);
  if (token.type_ != type)
    return addError(message, token);
  return true;
}