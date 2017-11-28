static uint32
G(uint32 X, uint32 Y, uint32 Z)
{
    return (X & Y) | (X & Z) | (Y & Z);
}