const Acl::Options &
Acl::AnnotationStrategy::options()
{
    static const Acl::CharacterSetOption Delimiters;
    static const Acl::Options MyOptions = {
        { "-m", &Delimiters }
    };
    Delimiters.linkWith(&delimiters);
    return MyOptions;
}