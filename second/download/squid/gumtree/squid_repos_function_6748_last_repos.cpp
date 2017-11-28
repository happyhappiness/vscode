void
esiChoose::selectElement()
{
    if (chosenelement > -1)
        return;

    for (size_t counter = 0; counter < elements.size(); ++counter) {
        const esiWhen *el = dynamic_cast<esiWhen *>(elements[counter].getRaw());
        if (el && el->testsTrue()) {
            chosenelement = counter;
            debugs (86,3, "esiChooseAdd: Chose element " << counter + 1);
            return;
        }
    }
}