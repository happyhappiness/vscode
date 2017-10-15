#include "utils.h"
#include "window_log.h"

namespace display {

WindowLog::WindowLog(core::Log* l) :
  Window(new Canvas, 0, 0, 0, extent_full, extent_static),
  m_log(l) {

  m_taskUpdate.set_slot(rak::mem_fn(this, &WindowLog::receive_update)),

  // We're trying out scheduled tasks instead.
  m_connUpdate = l->signal_update().connect(sigc::mem_fun(*this, &WindowLog::receive_update));
}

WindowLog::~WindowLog() {
  priority_queue_erase(&taskScheduler, &m_taskUpdate);
  m_connUpdate.disconnect();
}

WindowLog::iterator
WindowLog::find_older() {
  return m_log->find_older(cachedTime - rak::timer::from_seconds(60));
}

void
WindowLog::redraw() {
  m_canvas->erase();

  int pos = m_canvas->height();

  for (core::Log::iterator itr = m_log->begin(), last = find_older(); itr != last && pos > 0; ++itr, --pos) {
    char buffer[16];
    print_hhmmss_local(buffer, buffer + 16, static_cast<time_t>(itr->first.seconds()));

    m_canvas->print(0, pos - 1, "(%s) %s", buffer, itr->second.c_str());
  }
}

// When WindowLog is activated, call receive_update() to ensure it
// gets updated.
void
WindowLog::receive_update() {
  if (!is_active())
    return;

  iterator itr = find_older();
  extent_type height = std::min(std::distance(m_log->begin(), itr), (std::iterator_traits<iterator>::difference_type)10);

  if (height != m_maxHeight) {
    m_minHeight = height != 0 ? 1 : 0;
    m_maxHeight = height;
    m_slotAdjust();

  } else {
    mark_dirty();
  }

  priority_queue_erase(&taskScheduler, &m_taskUpdate);

  if (height != 0)
    priority_queue_insert(&taskScheduler, &m_taskUpdate, (cachedTime + rak::timer::from_seconds(30)).round_seconds());
}

}
