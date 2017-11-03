inline void
priority_queue_insert(priority_queue_default* queue, priority_item* item, timer t) {
  if (t == timer())
    throw std::logic_error("priority_queue_insert(...) received a bad timer.");

  if (!item->is_valid())
    throw std::logic_error("priority_queue_insert(...) called on an invalid item.");

  if (item->is_queued())
    throw std::logic_error("priority_queue_insert(...) called on an already queued item.");

  if (queue->find(item) != queue->end())
    throw std::logic_error("priority_queue_insert(...) item found in queue.");

  item->set_time(t);
  queue->push(item);
}