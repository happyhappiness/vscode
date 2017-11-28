virtual void print(std::ostream &os) const {
        os << '(' << callback_data << ", err=" << errflag << ')';
    }