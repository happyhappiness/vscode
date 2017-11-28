static uint32
F(uint32 X, uint32 Y, uint32 Z)
{
    return (X & Y) | ((~X) & Z);
}