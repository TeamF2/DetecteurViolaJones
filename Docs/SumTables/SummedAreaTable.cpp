#include "SummedAreaTable.h"
#include <iostream>
#include <stdlib.h>
#include <iomanip>

//-----------------------------------------------------------------------------
SummedAreaTable::SummedAreaTable(
        unsigned int i_x,
        unsigned int i_y,
        const std::vector<double> i_values
        ):
    m_values(i_values),
    m_noOfValuesX(i_x),
    m_noOfValuesY(i_y)
{
   if(m_values.size()!= i_x*i_y)
   {
      std::cout << "ERROR: the len of the i_values is not equal to i_x*i_y\n";
      std::cout << "Len of i_values = " << m_values.size() << " " << i_values.size() << "\n";
      exit(EXIT_FAILURE);
   }

   // create summed table
   // first compute the first horizontal line
   for(unsigned int x=1; x < m_noOfValuesX;++x)
   {
      // no need to call getIndex because the y position is always 0
      m_values[x] += m_values[x-1];
   }
   // then compute the first vertical line
   for(unsigned int y=1; y < m_noOfValuesY; ++y)
   {
      m_values[getIndex(0,y)] += m_values[getIndex(0,y-1)];
   }
   // and finally the rest values
   for(unsigned int x=1; x < m_noOfValuesX; ++x)
   {
      for (unsigned int y=1; y < m_noOfValuesY; ++y)
      {
          m_values[getIndex(x,y)] += m_values[getIndex(x-1,y)]
                  + m_values[getIndex(x,y-1)] - m_values[getIndex(x-1,y-1)];
      }
   }
}

//-----------------------------------------------------------------------------
unsigned short int SummedAreaTable::getIndex(
        unsigned int short i_x,
        unsigned short int i_y
        )const
{
    return i_x+i_y*m_noOfValuesX;
}


//-----------------------------------------------------------------------------
double SummedAreaTable::getSumOfArea(
        unsigned short i_posX,
        unsigned short i_posY,
        unsigned short i_lenX,
        unsigned short i_lenY
        ) const
{
   if(i_posX==0 && i_posY==0)
   {
      return m_values[getIndex(i_lenX,i_lenY)];
   }
   if(i_posX==0)
   {
       return m_values[getIndex(i_lenX,i_posY+i_lenY)]
               -m_values[getIndex(i_posX,i_posY-1)];
   }
   if(i_posY==0)
   {
       return m_values[getIndex(i_posX+i_lenX,i_lenY)]
               -m_values[getIndex(i_posX-1,i_lenY)];
   }
   return   m_values[getIndex(i_posX-1     , i_posY-1)     ]
          + m_values[getIndex(i_posX+i_lenX, i_posY+i_lenY)]
          - m_values[getIndex(i_posX+i_lenX, i_posY-1)     ]
          - m_values[getIndex(i_posX-1     , i_posY+i_lenY)];
}


//-----------------------------------------------------------------------------
void SummedAreaTable::print()const
{
   std::cout << "Table size = " << m_noOfValuesX << " x "
             << m_noOfValuesY << "\n";
   for(unsigned int i=0; i < m_values.size(); ++i)
   {
       if(i%m_noOfValuesX==0)
       {
          std::cout << "\n";
       }
       std::cout << " " << std::setw(6) << std::setprecision(4) <<  m_values[i];
   }
   std::cout << "\n\n";
}

//-----------------------------------------------------------------------------
SummedAreaTable::~SummedAreaTable()
{}
