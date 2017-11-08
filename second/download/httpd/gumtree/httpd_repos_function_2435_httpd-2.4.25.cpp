static const char *policy_str(h2_push_policy policy)
{
    switch (policy) {
        case H2_PUSH_NONE:
            return "none";
        case H2_PUSH_FAST_LOAD:
            return "fast-load";
        case H2_PUSH_HEAD:
            return "head";
        default:
            return "default";
    }
}