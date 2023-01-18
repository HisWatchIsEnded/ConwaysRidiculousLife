//
// Created by Dan on 1/17/2023.
//

#ifndef CONWAYSRIDICULOUSLIFE_LIFE_H
#define CONWAYSRIDICULOUSLIFE_LIFE_H

#include <cstdint>
#include <vector>

namespace GameOf
{

class Life
{
public:
  Life(uint64_t width, uint64_t height);
  virtual ~Life();
  void AddSeedCell(std::tuple<uint64_t, uint64_t> newPoint );
  void SetCellState(uint64_t x, uint64_t y, bool alive);
  void Evolve( int iterations );
  void OutputState();

private:
  static const uint64_t MAP_SIZE = UINT64_MAX;
  unsigned char* population;
  unsigned char* evolution;
  uint64_t byteLength;
};

} // GameOf

#endif //CONWAYSRIDICULOUSLIFE_LIFE_H
