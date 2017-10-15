
#include "config.h"

#include <rak/algorithm.h>

#include "core/download.h"

#include "canvas.h"
#include "globals.h"
#include "utils.h"
#include "window_download_list.h"

namespace display {

WindowDownloadList::WindowDownloadList(DList* l) :
  Window(new Canvas, true),
  m_list(l) {

  m_connChanged = m_list->signal_changed().connect(sigc::mem_fun(*this, &Window::mark_dirty));
}

WindowDownloadList::~WindowDownloadList() {
  m_connChanged.disconnect();
}

void
WindowDownloadList::redraw() {
  m_slotSchedule(this, (cachedTime + rak::timer::from_seconds(1)).round_seconds());

  m_canvas->erase();

  if (m_list->base().empty() || m_canvas->get_width() < 5)
    return;

  typedef std::pair<DList::iterator, DList::iterator> Range;

  Range range = rak::advance_bidirectional(m_list->begin(),
					   m_list->get_focus() != m_list->end() ? m_list->get_focus() : m_list->begin(),
					   m_list->end(),
					   m_canvas->get_height() / 3);

  // Make sure we properly fill out the last lines so it looks like
  // there are more torrents, yet don't hide it if we got the last one
  // in focus.
  if (range.second != m_list->end())
    ++range.second;

  int pos = 0;

  while (range.first != range.second) {
    char buffer[m_canvas->get_width()];
    char* position;
    char* last = buffer + m_canvas->get_width() - 2;

    position = print_download_title(buffer, last, *range.first);
    m_canvas->print(0, pos++, "%c %s", range.first == m_list->get_focus() ? '*' : ' ', buffer);
    
    position = print_download_info(buffer, last, *range.first);
    m_canvas->print(0, pos++, "%c %s", range.first == m_list->get_focus() ? '*' : ' ', buffer);

    position = print_download_status(buffer, last, *range.first);
    m_canvas->print(0, pos++, "%c %s", range.first == m_list->get_focus() ? '*' : ' ', buffer);

    ++range.first;
  }    
}

}
