void
esiChoose::NULLUnChosen()
{
    if (chosenelement >= 0) {
        if (otherwise.getRaw())
            otherwise->finish();

        otherwise = NULL;

        elements.setNULL (0, chosenelement);

        elements.setNULL (chosenelement + 1, elements.size());
    } else if (otherwise.getRaw()) {
        elements.setNULL (0, elements.size());
    }
}