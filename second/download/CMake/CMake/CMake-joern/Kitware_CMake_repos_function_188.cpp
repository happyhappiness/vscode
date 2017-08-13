bool Reader::addErrorAndRecover(const std::string& message,
                                Token& token,
                                TokenType skipUntilToken) {
  addError(message, token);
  return recoverFromError(skipUntilToken);
}