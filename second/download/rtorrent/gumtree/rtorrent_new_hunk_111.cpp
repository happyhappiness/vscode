#include "poll_manager_epoll.h"
#include "poll_manager_select.h"

namespace core {

static void
connect_signal_network_log(Download* d, torrent::Download::slot_string_type s) {
  d->download()->signal_network_log(s);
}

static void
connect_signal_storage_log(Download* d, torrent::Download::slot_string_type s) {
  d->download()->signal_storage_error(s);
}

// Need a proper logging class for this.
static void
connect_signal_tracker_dump(Download* d, torrent::Download::slot_dump_type s) {
  if (!control->variable()->get_string("tracker_dump").empty())
    d->download()->signal_tracker_dump(s);
}

static void
receive_tracker_dump(const std::string& url, const char* data, size_t size) {
  const std::string& filename = control->variable()->get_string("tracker_dump");

  if (filename.empty())
    return;

  std::fstream fstr(filename.c_str(), std::ios::out | std::ios::app);

  if (!fstr.is_open())
    return;

  fstr << "url: " << url << std::endl << "---" << std::endl;
  fstr.write(data, size);
  fstr << std::endl <<"---" << std::endl;
}

// Hmm... find some better place for all this.
static void
delete_tied(Download* d) {
  const std::string tie = d->variable()->get("tied_to_file").as_string();

  // This should be configurable, need to wait for the variable
  // thingie to be implemented.
  if (!tie.empty())
    ::unlink(tie.c_str());
}
