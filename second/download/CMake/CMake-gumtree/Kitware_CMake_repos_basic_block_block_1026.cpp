{
            messages->push_back(Message(
              Glob::error, "Canonical path generation from path '" + dir +
                "' failed! Reason: '" + realPathErrorMessage + "'"));
          }