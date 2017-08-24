{
  if (!root.hasComment(commentBefore))
    return;

  document_ += "\n";
  writeIndent();
  std::string normalizedComment = normalizeEOL(root.getComment(commentBefore));
  std::string::const_iterator iter = normalizedComment.begin();
  while (iter != normalizedComment.end()) {
    document_ += *iter;
    if (*iter == '\n' && *(iter + 1) == '/')
      writeIndent();
    ++iter;
  }

  // Comments are stripped of newlines, so add one here
  document_ += "\n";
}