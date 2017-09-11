                rdbCheckError("Invalid object type: %d", type);
                return 1;
            }
            rdbstate.key_type = type;
        }

        /* Read key */
