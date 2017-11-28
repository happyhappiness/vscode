Helper::Xaction *
helper::nextRequest()
{
    if (queue.empty())
        return nullptr;

    auto *r = queue.front();
    queue.pop();
    --stats.queue_size;
    return r;
}