virtual Mgr::Action::Pointer create(const Mgr::Command::Pointer &cmd) const {
        return handler(cmd);
    }