void dereference(C const *newP = NULL) {
        /* Setting p_ first is important:
        * we may be freed ourselves as a result of
        * delete p_;
        */
        C const (*tempP_) (p_);
        p_ = newP;

        if (tempP_ && tempP_->unlock() == 0)
            delete tempP_;
    }