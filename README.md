# ToolSet_ILCSOFT

This package includes many basic functions for making ILCSOFT easier to use.

- How to load this library

    in any Processor's CMakeList.txt, add these two commands.

	```
		INCLUDE_DIRECTORIES( "/the/absolute/path/for/Tool_Set/src" )
		 LINK_LIBRARIES     ( "/the/absolute/path/for/Tool_Set/libtoolset.so" )

   	```

    Then you can use the functions in this ToolSet library as others.

- How to use functions in this library

   - First, include the correct header file, e.g. when you use Get_MCParticles_Information(LCCollection* mccol), you need to include CMC.h file
   ```
	 #include "CMC.h"
   ```

	- When load the function use the command,  include the namespace and class name:
	```
		std::vector<MCParticle*> MCs          =ToolSet::CMC::Get_MCParticle(mccol);

	```

	- of course, you can using namespace ToolSet, to include all functions in this namespace in the beginning of the Code.

Hope you to like this package.

