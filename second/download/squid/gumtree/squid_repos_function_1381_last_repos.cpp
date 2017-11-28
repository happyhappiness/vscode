bool
helper::overloaded() const {
    return stats.queue_size > static_cast<int>(childs.queue_size);
}