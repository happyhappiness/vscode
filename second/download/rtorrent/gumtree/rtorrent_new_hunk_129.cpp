
#include "config.h"

#include <rak/algorithm.h>

#include "core/download.h"
#include "core/view.h"

#include "canvas.h"
#include "globals.h"
#include "utils.h"
#include "window_download_list.h"

namespace display {

WindowDownloadList::~WindowDownloadList() {
  m_connChanged.disconnect();
}

void
WindowDownloadList::set_view(core::View* l) {
  m_view = l;

  m_connChanged.disconnect();

  if (m_view != NULL)
    m_connChanged = m_view->signal_changed().connect(sigc::mem_fun(*this, &Window::mark_dirty));
}

void
WindowDownloadList::redraw() {
  m_slotSchedule(this, (cachedTime + rak::timer::from_seconds(1)).round_seconds());

  m_canvas->erase();

  if (m_view == NULL)
    return;

  m_canvas->print(0, 0, "%s", ("[View: " + m_view->name() + "]").c_str());

  if (m_view->empty() || m_canvas->get_width() < 5 || m_canvas->get_height() < 2)
    return;

  typedef std::pair<core::View::iterator, core::View::iterator> Range;

  Range range = rak::advance_bidirectional(m_view->begin(),
					   m_view->focus() != m_view->end() ? m_view->focus() : m_view->begin(),
					   m_view->end(),
					   m_canvas->get_height() / 3);

  // Make sure we properly fill out the last lines so it looks like
  // there are more torrents, yet don't hide it if we got the last one
  // in focus.
  if (range.second != m_view->end())
    ++range.second;

  int pos = 1;

  while (range.first != range.second) {
    char buffer[m_canvas->get_width()];
    char* position;
    char* last = buffer + m_canvas->get_width() - 2;

    position = print_download_title(buffer, last, *range.first);
    m_canvas->print(0, pos++, "%c %s", range.first == m_view->focus() ? '*' : ' ', buffer);
    
    position = print_download_info(buffer, last, *range.first);
    m_canvas->print(0, pos++, "%c %s", range.first == m_view->focus() ? '*' : ' ', buffer);

    position = print_download_status(buffer, last, *range.first);
    m_canvas->print(0, pos++, "%c %s", range.first == m_view->focus() ? '*' : ' ', buffer);

    ++range.first;
  }    
}

}
