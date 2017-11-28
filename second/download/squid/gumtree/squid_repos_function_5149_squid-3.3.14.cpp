void
authenticateRotate(void)
{
    for (Auth::ConfigVector::iterator i = Auth::TheConfig.begin(); i != Auth::TheConfig.end(); ++i)
        if ((*i)->configured())
            (*i)->rotateHelpers();
}