virtual void print(std::ostream &os) const {
        startPrint(os) <<
        ", " << FdNote(portTypeNote) << " port=" << (void*)portCfg << ')';
    }