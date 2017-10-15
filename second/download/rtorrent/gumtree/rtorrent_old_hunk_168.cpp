#include "utils.h"
#include "window_log.h"

namespace display {

WindowLog::WindowLog(core::Log* l) :
  Window(new Canvas, false, 0),
  m_log(l) {

  m_active = false;

  // We're trying out scheduled tasks instead.
  m_connUpdate = l->signal_update().connect(sigc::mem_fun(*this, &WindowLog::receive_update));
}

WindowLog::~WindowLog() {
  m_connUpdate.disconnect();
}

WindowLog::iterator
WindowLog::find_older() {
  return m_log->find_older(cachedTime - rak::timer::from_seconds(60));
}

void
WindowLog::redraw() {
  m_canvas->erase();

  int pos = 0;

  for (core::Log::iterator itr = m_log->begin(), end = find_older(); itr != end && pos < m_canvas->get_height(); ++itr) {
    char buffer[16];
    print_hhmmss_local(buffer, buffer + 16, static_cast<time_t>(itr->first.seconds()));

    m_canvas->print(0, pos++, "(%s) %s", buffer, itr->second.c_str());
  }
}

void
WindowLog::receive_update() {
  iterator itr = find_older();
  int h = std::min(std::distance(m_log->begin(), itr), (std::iterator_traits<iterator>::difference_type)10);

  if (h != m_minHeight) {
    set_active(h != 0);

    m_minHeight = h;
    m_slotAdjust();
  }

  mark_dirty();
}

}
