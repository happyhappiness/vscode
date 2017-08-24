{
  if (!root.hasComment(commentBefore))
    return;
  *document_ << normalizeEOL(root.getComment(commentBefore));
  *document_ << "\n";
}