static void
FreeObject(void *address)
{
    StoreSwapLogData *anObject = static_cast <StoreSwapLogData *>(address);
    delete anObject;
}