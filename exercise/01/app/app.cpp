#include "pch.h"
#include <iostream>
#include "../lib/public.h"
#include "../dll2/public.h"
#include <Windows.h>

typedef double(__cdecl *GET_VALUE_FUNCTION)(int input);

int main()
{
  // Static library
  double input = 100.0;
  double resultStatic = static_lib::get_value(input);
  std::cout << "Static library -> Input = " << input
    << " Result = " << resultStatic << std::endl;

  // Dynamic library
  const HMODULE handle = LoadLibraryA("dynamic_library.dll");

  if (handle != nullptr)
  {
    GET_VALUE_FUNCTION function = (GET_VALUE_FUNCTION) GetProcAddress(handle, "get_value");
    double resultDynamic = function(input);

    std::cout << "Dynamic library -> Input = " << input 
      << " Result = " << resultDynamic << std::endl;
    FreeLibrary(handle);
  }
  else
  {
    std::cout << "Loading of dynamic_library.dll failed!" << std::endl;
  }

  // dynamic_library with implib
  double resultDynamicWithImpl = get_value(input);
  std::cout << "Dynamic library with implib -> Input = " << input
    << " Result = " << resultDynamicWithImpl << std::endl;
}
