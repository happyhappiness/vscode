void
HttpHdrSc::setMaxAge(char const *target, int max_age)
{
    HttpHdrScTarget *sct = findTarget(target);

    if (!sct) {
        sct = new HttpHdrScTarget(target);
        dlinkAddTail (sct, &sct->node, &targets);
    }

    sct->maxAge(max_age);
}