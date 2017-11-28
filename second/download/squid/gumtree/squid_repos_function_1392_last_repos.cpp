bool
helper::willOverload() const {
    return queueFull() && !(childs.needNew() || GetFirstAvailable(this));
}