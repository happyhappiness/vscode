void
ESIVarState::removeVariable (String const &name)
{
    Variable *candidate = static_cast <Variable *>(variables.find (name.rawBuf(), name.size()));

    if (candidate) {
        /* XXX: remove me */
        /* Note - this involves:
         * extend libTrie to have a remove() call.
         * delete from the vector.
         * delete the object.
         */
    }
}