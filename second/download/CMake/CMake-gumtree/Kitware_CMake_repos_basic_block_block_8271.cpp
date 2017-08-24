{
    // Remove newline characters at the end of the comments
    size_t lastNonNewline = commentsBefore_.find_last_not_of("\r\n");
    if (lastNonNewline != std::string::npos) {
      commentsBefore_.erase(lastNonNewline + 1);
    } else {
      commentsBefore_.clear();
    }

    currentValue().setComment(commentsBefore_, commentBefore);
    commentsBefore_ = "";
  }