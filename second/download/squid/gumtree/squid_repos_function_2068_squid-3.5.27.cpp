void
StoreController::transientsDisconnect(MemObject &mem_obj)
{
    if (transients)
        transients->disconnect(mem_obj);
}