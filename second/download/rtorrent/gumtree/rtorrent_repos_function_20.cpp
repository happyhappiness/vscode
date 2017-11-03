inline void
priority_queue_erase(priority_queue_default* queue, priority_item* item) {
  if (!item->is_queued())
    return;

  // Check is_valid() after is_queued() so that it is safe to call
  // erase on untouched instances.
  if (!item->is_valid())
    throw std::logic_error("priority_queue_erase(...) called on an invalid item.");

  // Clear time before erasing to force it to the top.
  item->clear_time();
  
  if (!queue->erase(item))
    throw std::logic_error("priority_queue_erase(...) could not find item in queue.");

  if (queue->find(item) != queue->end())
    throw std::logic_error("priority_queue_erase(...) item still in queue.");
}