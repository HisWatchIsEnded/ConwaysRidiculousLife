//
// Created by Dan on 1/17/2023.
//

#include "Life.h"

namespace GameOf
{

///
/// This implementation of "Life" relies on bit-packing cells.
/// a given cell is typed as a `char` (8 bits), where the zeroth bit is the alive state,
/// and the first through fourth bit store the number of alive neighbors (min: 0, max: 8).
///
/// The size for the field is anywhere within the int64_t register: theoretically,
/// INT64_MAX ^ 2 - this is unregisterable. The following is an attempt to create a sparse
/// list of cells, to store only live cells using a `char` as described above.
///
/// To avoid issues with overflow / underflow each seed cell will be shifted to the
/// unsigned space (uint64_t) upon ingest, and shifted back to the signed space
/// (int64_t) for writing into output format.
///

Life::Life(uint64_t width, uint64_t height)
{
  byteLength = width * height;
  population = new unsigned char[byteLength];
  evolution = new unsigned char[byteLength];
  memset(population, 0, byteLength);
  memset(evolution, 0, byteLength);
}

Life::~Life()
{
  delete[] population;
  delete[] evolution;
}

void Life::AddSeedCell(std::tuple<uint64_t, uint64_t> newPoint)
{
  SetCellState(std::get<0>(newPoint), std::get<1>(newPoint), true);
}

void Life::SetCellState(uint64_t x, uint64_t y, bool alive)
{
  unsigned char *targetCell = population + (y * MAP_SIZE) + x;

  uint64_t xOffsetLeft, xOffsetRight, yOffsetUp, yOffsetDown;
  xOffsetLeft = ( x == 0) ? MAP_SIZE - 1 : -1;
  xOffsetRight = ( x == (MAP_SIZE - 1)) ? -(MAP_SIZE - 1) : 1;
  yOffsetUp = ( y == 0 ) ? byteLength - MAP_SIZE : MAP_SIZE;
  yOffsetDown = ( y == ( MAP_SIZE - 1 )) ? -(byteLength - MAP_SIZE) : MAP_SIZE;

  if( alive )
  {
    *(targetCell) |= 0x01;
    *(targetCell + yOffsetUp + xOffsetLeft) += 0x02;
    *(targetCell + yOffsetUp) += 0x02;
    *(targetCell + yOffsetUp + xOffsetRight) += 0x02;
    *(targetCell + xOffsetLeft) += 0x02;
    *(targetCell + xOffsetRight) += 0x02;
    *(targetCell + yOffsetDown + xOffsetLeft) += 0x02;
    *(targetCell + yOffsetDown) += 0x02;
    *(targetCell + yOffsetDown + xOffsetRight) += 0x02;
  }
  else
  {
    *(targetCell) &= ~0x01;
    *(targetCell + yOffsetUp + xOffsetLeft) -= 0x02;
    *(targetCell + yOffsetUp) -= 0x02;
    *(targetCell + yOffsetUp + xOffsetRight) -= 0x02;
    *(targetCell + xOffsetLeft) -= 0x02;
    *(targetCell + xOffsetRight) -= 0x02;
    *(targetCell + yOffsetDown + xOffsetLeft) -= 0x02;
    *(targetCell + yOffsetDown) -= 0x02;
    *(targetCell + yOffsetDown + xOffsetRight) -= 0x02;
  }
}

void Life::Evolve(int iterations)
{
  int64_t x, y;
  unsigned int neighborCount;
  unsigned char *cellPointer;
  memcpy( evolution, population, byteLength);
  cellPointer = evolution;

  while(iterations > 0)
  {
    for ( y = 0; y < MAP_SIZE; y++ )
    {
      x = 0;
      do
      {
        while( *cellPointer == 0)
        {
          cellPointer++;
          if(++x >= MAP_SIZE)
          {
            goto NextRow;
          }
        }

        neighborCount = *cellPointer >> 1;
        if ( *cellPointer & 0x01 )
        {
          if(( neighborCount != 2) && (neighborCount != 3))
          {
            SetCellState( x, y, false);
          }
        }
        else
        {
          if (neighborCount == 3)
          {
            SetCellState( x, y, true);
          }
        }
      }
      while (++x < MAP_SIZE);
      NextRow:;
    }

    iterations--;
  }
}

void Life::OutputState()
{

}

} // GameOf