#include "Wrench_Logging.h"
#include <fstream>

namespace Wrench
{
	void Print( WString message )
	{
		std::cout << message;
	}

	void Print( WString message, COL color )
	{
	#ifdef WRENCH_WINDOWS
		HANDLE han = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute( han, color );
		std::cout << message;
		SetConsoleTextAttribute( han, 0x07);
    #else
        //Linux
        std::cout << "\033[0" << color << "m " << message;
    #endif
	}


	void Print( WString message, COL foreground, COL background )
	{
	#ifdef WRENCH_WINDOWS
		HANDLE han = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute( han, foreground + background);
			std::cout << message;
		SetConsoleTextAttribute( han, 0x07);
    #else
        //Linux
        std::cout << "\033[0" << foreground << ";" << background << "m " << message;
    #endif
	}


	void Printfile( WString message, bool truncate, char* path )
	{
        #ifdef WRENCH_WINDOWS
            int flags;
		#else
            std::ios_base::openmode flags;
		#endif

		if(truncate)
			flags = std::ofstream::binary | std::ios::trunc;
		else
			flags = std::ofstream::binary | std::ios::app;


            std::ofstream fs;
            fs.open(path, flags);
            fs << message << std::endl;

	}

	void Printfile( WString message, int placement, WString ix, bool truncate, WString path )
	{
        #ifdef WRENCH_WINDOWS
            int flags;
		#else
            std::ios_base::openmode flags;
		#endif

		if(truncate)
			flags = std::ofstream::binary | std::ios::trunc;
		else
			flags = std::ofstream::binary | std::ios::app;


        std::ofstream fs;
        fs.open(path, flags);

		switch(placement)
		{
			case Wrench::PLACEMENT_PREFIX:
				fs << ix << message << std::endl;
				break;
			case Wrench::PLACEMENT_SUFFIX:
				fs << message << ix << std::endl;
				break;
		}

	}

	void Printfile( WString message, WString prefix, WString suffix, bool truncate, WString path )
	{
        #ifdef WRENCH_WINDOWS
            int flags;
		#else
            std::ios_base::openmode flags;
		#endif

		if(truncate)
			flags = std::ofstream::binary | std::ios::trunc;
		else
			flags = std::ofstream::binary | std::ios::app;


        std::ofstream fs;
        fs.open(path, flags);
		fs << prefix << message << suffix << std::endl;
	}


}
