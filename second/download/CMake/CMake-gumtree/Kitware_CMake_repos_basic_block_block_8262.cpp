{
  if (!features_.allowComments_) {
    collectComments = false;
  }

  begin_ = beginDoc;
  end_ = endDoc;
  collectComments_ = collectComments;
  current_ = begin_;
  lastValueEnd_ = 0;
  lastValue_ = 0;
  commentsBefore_ = "";
  errors_.clear();
  while (!nodes_.empty())
    nodes_.pop();
  nodes_.push(&root);

  bool successful = readValue();
  Token token;
  skipCommentTokens(token);
  if (collectComments_ && !commentsBefore_.empty())
    root.setComment(commentsBefore_, commentAfter);
  if (features_.strictRoot_) {
    if (!root.isArray() && !root.isObject()) {
      // Set error location to start of doc, ideally should be first token found
      // in doc
      token.type_ = tokenError;
      token.start_ = beginDoc;
      token.end_ = endDoc;
      addError(
          "A valid JSON document must be either an array or an object value.",
          token);
      return false;
    }
  }
  return successful;
}