(w == &loop->signal_io_watcher) {
          have_signals = 1;
        } else {
          w->cb(loop, w, pe->revents);
        }