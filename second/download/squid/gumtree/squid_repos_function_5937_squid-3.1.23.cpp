void reference (const RefCount& p) {
        if (p.p_)
            p.p_->RefCountReference();
    }