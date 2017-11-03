void
CommandScheduler::call_item(value_type item) {
  if (item->is_queued())
    throw torrent::internal_error("CommandScheduler::call_item(...) called but item is still queued.");

  if (std::find(begin(), end(), item) == end())
    throw torrent::internal_error("CommandScheduler::call_item(...) called but the item isn't in the scheduler.");

  // Remove the item before calling the command if it should be
  // removed.

  try {
    rpc::parse_command_multiple_std(item->command());

  } catch (torrent::input_error& e) {
    if (m_slotErrorMessage.is_valid())
      m_slotErrorMessage("Scheduled command failed: " + item->key() + ": " + e.what());
  }

  // Still schedule if we caught a torrrent::input_error?
  rak::timer next = item->next_time_scheduled();

  if (next == rak::timer()) {
    // Remove from scheduler?
    return;
  }

  if (next <= cachedTime)
    throw torrent::internal_error("CommandScheduler::call_item(...) tried to schedule a zero interval item.");

  item->enable(next);
}