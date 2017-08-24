{
  readToken(token);
  if (token.type_ != type)
    return addError(message, token);
  return true;
}