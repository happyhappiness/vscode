bool
esiTry::addElement(ESIElement::Pointer element)
{
    debugs(86, 5, "esiTryAdd: Try " << this << " adding element " <<
           element.getRaw());

    if (dynamic_cast<esiLiteral*>(element.getRaw())) {
        /* Swallow whitespace */
        debugs(86, 5, "esiTryAdd: Try " << this << " skipping whitespace " << element.getRaw());
        return true;
    }

    if (dynamic_cast<esiAttempt*>(element.getRaw())) {
        if (attempt.getRaw()) {
            debugs(86, DBG_IMPORTANT, "esiTryAdd: Failed for " << this << " - try allready has an attempt node (section 3.4)");
            return false;
        }

        attempt = element;
        return true;
    }

    if (dynamic_cast<esiExcept*>(element.getRaw())) {
        if (except.getRaw()) {
            debugs(86, DBG_IMPORTANT, "esiTryAdd: Failed for " << this << " - try already has an except node (section 3.4)");
            return false;
        }

        except = element;
        return true;
    }

    debugs(86, DBG_IMPORTANT, "esiTryAdd: Failed to add element " << element.getRaw() << " to try " << this << ", incorrect element type (see section 3.4)");
    return false;
}