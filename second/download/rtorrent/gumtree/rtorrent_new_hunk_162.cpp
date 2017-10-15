
#include "core/download.h"

namespace display {

WindowDownloadStatusbar::WindowDownloadStatusbar(core::Download* d) :
  Window(new Canvas, 0, 0, 3, extent_full, extent_static),
  m_download(d) {
}

void
WindowDownloadStatusbar::redraw() {
  m_slotSchedule(this, (cachedTime + rak::timer::from_seconds(1)).round_seconds());

  m_canvas->erase();

  char buffer[m_canvas->width()];
  char* position;
  char* last = buffer + m_canvas->width() - 2;

  position = print_download_info(buffer, last, m_download);
  m_canvas->print(0, 0, "%s", buffer);

  position = buffer + std::max(snprintf(buffer, last - buffer, "Peers: %i(%i) Min/Max: %i/%i Uploads: %i U/I/C/A: %i/%i/%i/%i Failed: %i",
					(int)m_download->download()->peers_connected(),
