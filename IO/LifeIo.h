//
// Created by Dan on 1/17/2023.
//

#ifndef CONWAYSRIDICULOUSLIFE_LIFEIO_H
#define CONWAYSRIDICULOUSLIFE_LIFEIO_H

#include <cstdint>
#include <string>
#include <sstream>
#include <vector>

namespace LifeIO
{

static const std::string LIFE_IO_1_06_HEADER = "#Life 1.06";
static const char COORD_DELIMITER = ' ';
static const char END_LINE = '\n';

static std::vector<std::string> split(const std::string& inString, char delimiter)
{
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(inString);
  while (std::getline(tokenStream, token, delimiter))
  {
    tokens.push_back(token);
  }
  return tokens;
}

uint64_t shiftToUnsigned( int64_t input )
{
  uint64_t shifted = UINT64_MAX / 2;
  shifted += input + 1;
  return shifted;
}

int64_t shiftToSigned( uint64_t input )
{
  int64_t shifted = INT64_MIN;
  shifted += input;
  shifted -= 1;
  return shifted;
}

static std::tuple<int64_t, int64_t> PointFromLine( std::string newLine )
{
  std::vector<std::string> parsedCoords = split(newLine, COORD_DELIMITER);
  uint64_t x = shiftToUnsigned(std::stoi(parsedCoords[0]));
  uint64_t y = shiftToUnsigned(std::stoi(parsedCoords[1]));
  std::tuple<uint64_t, uint64_t> newPoint(x, y);
  return newPoint;
};

static std::string LineFromPoint( std::tuple<uint64_t, uint64_t> newPoint )
{
  std::string coords;
  coords += std::to_string(shiftToSigned(std::get<0>(newPoint)));
  coords += COORD_DELIMITER;
  coords += std::to_string(shiftToSigned(std::get<1>(newPoint)));
  coords += END_LINE;
  return coords;
};

} // LifeIO

#endif //CONWAYSRIDICULOUSLIFE_LIFEIO_H
