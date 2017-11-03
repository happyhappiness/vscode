void
PathInput::receive_do_complete() {
  size_type dirEnd = find_last_delim();

  utils::Directory dir(dirEnd != 0 ? str().substr(0, dirEnd) : "./");
  
  if (!dir.update() || dir.empty()) {
    mark_dirty();

    return;
  }

  std::for_each(dir.begin(), dir.end(), _transform_filename(str().substr(0, dirEnd)));

  Range r = find_incomplete(dir, str().substr(dirEnd, get_pos()));

  if (r.first == r.second)
    return; // Show some nice colors here.

  std::string base = rak::make_base(r.first, r.second);

  // Clear the path after the cursor to make this code cleaner. It's
  // not really nessesary to add the complexity just because someone
  // might start tab-completeing in the middle of a path.
  str().resize(dirEnd);
  str().insert(dirEnd, base);

  set_pos(dirEnd + base.size());

  mark_dirty();

  // Only emit if there are more than one option.
  m_showNext = ++utils::Directory::iterator(r.first) != r.second;

  if (m_showNext)
    m_signalShowRange.emit(r.first, r.second);
}