#include "poll_manager_epoll.h"
#include "poll_manager_select.h"

namespace core {

static void
connect_signal_network_log(Download* d, torrent::Download::SlotString s) {
  d->get_download().signal_network_log(s);
}

static void
connect_signal_storage_log(Download* d, torrent::Download::SlotString s) {
  d->get_download().signal_storage_error(s);
}

// Hmm... find some better place for all this.
static void
delete_tied(Download* d) {
  const std::string tie = d->variables()->get("tied_to_file").as_string();

  // This should be configurable, need to wait for the variable
  // thingie to be implemented.
  if (!tie.empty())
    ::unlink(tie.c_str());
}
