virtual void print(std::ostream &os) const {
        os << '(' << fwd_.get() << ", " << answer_ << ')';
    }