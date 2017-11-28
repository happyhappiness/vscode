AsyncCallQueue &
AsyncCallQueue::Instance()
{
    // TODO: how to remove this frequent check while supporting early calls?
    if (!TheInstance)
        TheInstance = new AsyncCallQueue();

    return *TheInstance;
}