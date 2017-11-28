bool
AsyncCallQueue::fire()
{
    const bool made = theHead != NULL;
    while (theHead != NULL)
        fireNext();
    return made;
}