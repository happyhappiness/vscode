                cmPolicies::NEW

              ? "NEW"

              : "OLD");



    if (targetType == cmState::EXECUTABLE) {

      /* Put the executable at a known location (for COPY_FILE).  */
