void
ESIContext::fail (ESIElement * source, char const *anError)
{
    setError();
    setErrorMessage (anError);
    fail ();
    send ();
}