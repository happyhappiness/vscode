int
compareintvoid(void * const &a, void * const &n)
{
    intnode *A = (intnode *)a;
    intnode *B = (intnode *)n;
    return A->i - B->i;
}