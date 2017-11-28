bool
esiRemove::addElement (ESIElement::Pointer element)
{
    if (!dynamic_cast<esiLiteral*>(element.getRaw())) {
        debugs(86, 5, "esiRemoveAdd: Failed for " << this);
        return false;
    }

    return true;
}