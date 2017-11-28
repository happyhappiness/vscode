virtual void visit(const Name &name, const Area &value) {
        meta.putExt(name.image().c_str(), value.toString().c_str());
    }