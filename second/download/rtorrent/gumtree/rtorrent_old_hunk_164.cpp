
#include "window_download_transfer_list.h"

namespace display {

WindowDownloadTransferList::WindowDownloadTransferList(core::Download* d, unsigned int *focus) :
  Window(new Canvas, true),
  m_download(d),
  m_focus(focus) {
}

void
WindowDownloadTransferList::redraw() {
  // TODO: Make this depend on tracker signal.
  m_slotSchedule(this, (cachedTime + rak::timer::from_seconds(1)).round_seconds());
  m_canvas->erase();

  if (m_canvas->get_height() < 3 || m_canvas->get_width() < 18)
    return;

  const torrent::TransferList* transfers = m_download->download()->transfer_list();

  m_canvas->print(2, 0, "Transfer list: [Size %i]", transfers->size());

  torrent::TransferList::const_iterator itr = transfers->begin();

  // This is just for testing and the layout and included information
  // is just something i threw in there, someone really should
  // prettify this. (This is a very subtle hint)

  for (int y = 1; y < m_canvas->get_height() && itr != transfers->end(); ++y, ++itr) {
    m_canvas->print(0, y, "%5u [P: %u F: %u]", (*itr)->index(), (*itr)->priority(), (*itr)->failed());

    // Handle window size.
    for (torrent::BlockList::const_iterator bItr = (*itr)->begin(), bLast = (*itr)->end(); bItr != bLast; ++bItr) {
      char id;
      chtype attr = A_NORMAL;
