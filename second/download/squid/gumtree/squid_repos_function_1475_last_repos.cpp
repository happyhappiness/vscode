double
Math::Log(double x)
{
    assert((x + 1.0) >= 0.0);
    return log(x + 1.0);
}