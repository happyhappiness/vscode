void
esiTry::finish()
{
    parent = NULL;

    if (attempt.getRaw())
        attempt->finish();

    attempt = NULL;

    if (except.getRaw())
        except->finish();

    except = NULL;
}