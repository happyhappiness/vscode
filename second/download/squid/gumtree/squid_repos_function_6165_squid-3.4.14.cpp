void
ESIVariableProcessor::doFunction()
{
    if (!currentFunction)
        return;

    /* stay in here whilst operating */
    while (pos < len && state)
        switch (state) {

        case 2: /* looking for variable name */

            if (!validChar(string[pos])) {
                /* not a variable name char */

                if (pos - var_pos) {
                    vartype = varState->GetVar (string + var_pos, pos - var_pos);
                }

                state = 3;
            } else {
                ++pos;
            }

            break;

        case 3: /* looking for variable subref, end bracket or default indicator */

            if (string[pos] == ')') {
                /* end of string */
                eval(vartype, found_subref, found_default);
                done_pos = ++pos;
                safe_free(found_subref);
                safe_free(found_default);
                state = LOOKFORSTART;
            } else if (!found_subref && !found_default && string[pos] == '{') {
                debugs(86, 6, "ESIVarStateDoIt: Subref of some sort");
                /* subreference of some sort */
                /* look for the entry name */
                var_pos = ++pos;
                state = 4;
            } else if (!found_default && string[pos] == '|') {
                debugs(86, 6, "esiVarStateDoIt: Default present");
                /* extract default value */
                state = 5;
                var_pos = ++pos;
            } else {
                /* unexpected char, not a variable after all */
                debugs(86, 6, "esiVarStateDoIt: unexpected char after varname");
                state = LOOKFORSTART;
                pos = done_pos + 2;
            }

            break;

        case 4: /* looking for variable subref */

            if (string[pos] == '}') {
                /* end of subref */
                found_subref = xstrndup (&string[var_pos], pos - var_pos + 1);
                debugs(86, 6, "esiVarStateDoIt: found end of variable subref '" << found_subref << "'");
                state = 3;
                ++pos;
            } else if (!validChar (string[pos])) {
                debugs(86, 6, "esiVarStateDoIt: found invalid char in variable subref");
                /* not a valid subref */
                safe_free(found_subref);
                state = LOOKFORSTART;
                pos = done_pos + 2;
            } else {
                ++pos;
            }

            break;

        case 5: /* looking for a default value */

            if (string[pos] == '\'') {
                /* begins with a quote */
                debugs(86, 6, "esiVarStateDoIt: found quoted default");
                state = 6;
                var_pos = ++pos;
            } else {
                /* doesn't */
                debugs(86, 6, "esiVarStateDoIt: found unquoted default");
                state = 7;
                ++pos;
            }

            break;

        case 6: /* looking for a quote terminate default value */

            if (string[pos] == '\'') {
                /* end of default */
                found_default = xstrndup (&string[var_pos], pos - var_pos + 1);
                debugs(86, 6, "esiVarStateDoIt: found end of quoted default '" << found_default << "'");
                state = 3;
            }

            ++pos;
            break;

        case 7: /* looking for } terminate default value */

            if (string[pos] == ')') {
                /* end of default - end of variable*/
                found_default = xstrndup (&string[var_pos], pos - var_pos + 1);
                debugs(86, 6, "esiVarStateDoIt: found end of variable (w/ unquoted default) '" << found_default << "'");
                eval(vartype,found_subref, found_default);
                done_pos = ++pos;
                safe_free(found_default);
                safe_free(found_subref);
                state = LOOKFORSTART;
            }

            ++pos;
            break;

        default:
            fatal("esiVarStateDoIt: unexpected state\n");
        }
}