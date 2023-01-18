#include <iostream>
#include <string>
#include "IO/LifeIo.h"
#include "GameOf/Life.h"

int main()
{
  GameOf::Life lifeState = {INT64_MAX, INT64_MAX};

  // parse input
  for ( std::string line; std::getline( std::cin, line ); )
  {
    std::size_t commentLine = line.find(LifeIO::LIFE_IO_1_06_HEADER);
    if( commentLine != std::string::npos )
    {
      //ignore file header
      continue;
    }
    else
    {
      //read coords
      lifeState.AddSeedCell(LifeIO::PointFromLine(line));
    }
  }
  lifeState.Evolve(10 );
  //output state

  return 0;
}
