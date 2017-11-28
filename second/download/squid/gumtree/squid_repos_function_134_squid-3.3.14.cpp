void
SplayCheck::WalkVoid(void *const &node, void *state)
{
    intnode *A = (intnode *)node;
    CheckNode(*A);
}