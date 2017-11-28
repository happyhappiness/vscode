virtual void print(std::ostream &os) const {
            os << '(' << tunnel_.get() << ", " << answer_ << ')';
        }