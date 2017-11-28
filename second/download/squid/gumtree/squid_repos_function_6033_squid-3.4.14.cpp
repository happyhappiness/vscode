void
esiComment::render(ESISegment::Pointer output)
{
    /* Comments do nothing dude */
    debugs(86, 5, "esiCommentRender: Rendering comment " << this << " into " << output.getRaw());
}