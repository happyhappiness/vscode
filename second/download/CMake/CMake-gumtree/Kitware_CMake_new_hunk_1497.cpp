        sprintf(rpstr, "_p%d_", cc++);

        }

      while ( !done );

      }



    // Insert the newly mapped object file name.

    std::map<cmStdString, cmStdString>::value_type e(sin, ssin);

    it = m_UniqueObjectNamesMap.insert(e).first;

    }



  // Return the map entry.

  return it->second;

}



//----------------------------------------------------------------------------

