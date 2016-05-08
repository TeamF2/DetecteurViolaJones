#include <iostream>
#include <vector>
#include "SummedAreaTable.h"

int main(void)
{
   std::vector<double> values;

   double valuesArray [24]= {1.0, 2.0, 6.0, 7.0,
                             5.0, 7.0, 3.0, 2.0,
                             4.5, 5.5, 2.5, 8.5,
                             9.0, 0.5, 0.0, 4.0,
                             2.0, 0.0, 6.5, 8.0,
                             8.0, 0.0, 2.0, 9.5};

   values.assign(valuesArray,valuesArray+24);
   SummedAreaTable m_sumAreaTable(4,6,values);

   m_sumAreaTable.print();

   std::cout << "sum of area (1,2) till (3,5) = " << m_sumAreaTable.getSumOfArea(1,2,2,3) << "\n";
   std::cout << "sum of area (0,1) till (0,3) = " << m_sumAreaTable.getSumOfArea(0,1,0,2) << "\n";
   std::cout << "sum of area (0,1) till (1,3) = " << m_sumAreaTable.getSumOfArea(0,1,1,2) << "\n";
   std::cout << "sum of area (2,0) till (2,4) = " << m_sumAreaTable.getSumOfArea(2,0,0,4) << "\n";

   return 0;
}
