#ifndef SUMMEDAREATABLE_H
#define SUMMEDAREATABLE_H

#include <vector>

class SummedAreaTable
{
public:
   //--------------------------------------------------------------------------
   /// @brief contructor
   /// @param[in] i_x the number of values in the x-axis
   /// @param[in] i_y the number of values in the y-axis
   /// @param[in] i_tableValues
   //--------------------------------------------------------------------------
   SummedAreaTable(
           unsigned int i_x,
           unsigned int i_y,
           const std::vector<double> i_tableValues
           );
   //--------------------------------------------------------------------------
   /// @brief copy constructor
   //--------------------------------------------------------------------------
   SummedAreaTable(const SummedAreaTable &i_sumTable);
   //--------------------------------------------------------------------------
   /// @brief method that prints the values of the table
   //--------------------------------------------------------------------------
   void print()const;
   //--------------------------------------------------------------------------
   /// @brief method that returns the sum of the given area
   /// @param[in] i_posX the min X position of the area of our interest
   /// @param[in] i_posY the min Y position of the area of our interest
   /// @param[in] i_lenX the length of the area in the x-axis
   /// @param[in] i_lenY the length of the area in the y-axis
   //--------------------------------------------------------------------------
   double getSumOfArea(
           unsigned short int i_posX,
           unsigned short int i_posY,
           unsigned short int i_lenX,
           unsigned short int i_lenY
           )const;
   //--------------------------------------------------------------------------
   /// @brief default destractor
   //--------------------------------------------------------------------------
   ~SummedAreaTable();

private:
   //--------------------------------------------------------------------------
   /// @brief method that returns the index of a value in m_values
   /// @param[in] i_x the x position of the value on the table
   /// @param[in] i_y the y position of the value on the table
   //--------------------------------------------------------------------------
   unsigned short getIndex(unsigned short i_x, unsigned short i_y) const;

   //--------------------------------------------------------------------------
   /// @brief all the values of the sum table
   //--------------------------------------------------------------------------
   std::vector<double> m_values;
   //--------------------------------------------------------------------------
   /// @brief number of values in the x-axis
   //--------------------------------------------------------------------------
   unsigned short int m_noOfValuesX;
   //--------------------------------------------------------------------------
   /// @brief number of values in the y axis
   //--------------------------------------------------------------------------
   unsigned short int m_noOfValuesY;

};

#endif // SUMMEDAREATABLE_H
