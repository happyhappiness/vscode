int
DiskdIOStrategy::load()
{
    /* Calculate the storedir load relative to magic2 on a scale of 0 .. 1000 */
    /* the parse function guarantees magic2 is positivie */
    return away * 1000 / magic2;
}