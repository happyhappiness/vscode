inline void
priority_queue_perform(priority_queue_default* queue, timer t) {
  while (!queue->empty() && queue->top()->time() <= t) {
    priority_item* v = queue->top();
    queue->pop();

    v->clear_time();
    v->call();
  }
}