#include "manager.h"
#include "poll_manager_epoll.h"
#include "poll_manager_kqueue.h"
#include "poll_manager_select.h"
#include "view.h"

namespace std { using namespace tr1; }

namespace core {

void
Manager::handshake_log(const sockaddr* sa, int msg, int err, const torrent::HashString* hash) {
  if (!rpc::call_command_value("log.handshake"))
    return;
  
