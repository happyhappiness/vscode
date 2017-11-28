void
destintvoid(void * &data)
{
    intnode *i = (intnode *)data;
    xfree (i);
}