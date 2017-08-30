    CommandLineArguments::Internal::SetOfStrings::iterator sit;

    for ( sit = mpit->second.begin(); sit != mpit->second.end(); sit++ )

      {

      str << endl;

      char argument[100];

      sprintf(argument, sit->c_str());

      switch ( this->Internals->Callbacks[*sit].ArgumentType )

