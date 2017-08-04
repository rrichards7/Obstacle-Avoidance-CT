// IsInsideROI.cpp : Defines the exported functions for the DLL application.
//

#include <limits.h>
#include "stdafx.h"
#include "IsInsideROI.h"


/*
 * Elementary geometric Methods
 */


/*************************************************************************
   * FUNCTION:   CCW (CounterClockWise)
   *
   * PURPOSE
   * Determines, given three points, if when travelling from the first to
   * the second to the third, we travel in a counterclockwise direction.
   *
   * RETURN VALUE
   * (int) 1 if the movement is in a counterclockwise direction, -1 if
   * not. 0 for same points or for straight line.
   * This is basically a slope comparison: we don't do divisions because
   * of divide by zero possibilities with pure horizontal and pure
   * vertical lines.
   * Robert Sedgewick correction
 *************************************************************************/

 int CCW(POINT p0, POINT p1, POINT p2)
 {
   int dx1, dx2, dy1, dy2;

   dx1 = p1.x - p0.x ; dx2 = p2.x - p0.x ;
   dy1 = p1.y - p0.y ; dy2 = p2.y - p0.y ;

   if ( (dx1 * dy2) > (dy1 * dx2) )  return 1;
   if ( (dx1 * dy2) < (dy1 * dx2) )  return -1;
   if ( (dx1 * dy2) == (dy1 * dx2) ){
     if ( ( (dx1 * dx2) < 0) || ( (dy1 * dy2) < 0) ) return -1;
     else if ( (dx1 * dx1 + dy1 * dy1) >= (dx2 * dx2 + dy2 * dy2) ) return 0; else return 1;
   }
   else return 0;
 }

 /*************************************************************************
   * FUNCTION:   Intersect
   * PURPOSE
   * Given two line segments, determine if they intersect.
   * RETURN VALUE TRUE if they intersect, FALSE if not.
 *************************************************************************/

  BOOL Intersect(POINT p1, POINT p2, POINT p3, POINT p4)
  {
    int ccw11, ccw12, ccw21, ccw22;

    ccw11 = CCW(p1, p2, p3);
    ccw12 = CCW(p1, p2, p4);
    ccw21 = CCW(p3, p4, p1);
    ccw22 = CCW(p3, p4, p2);

   return ( ( ( (ccw11 * ccw12) < 0)
        &&  ( (ccw21 * ccw22) < 0) )
        ||   ( (ccw11 * ccw12 * ccw21 * ccw22) == 0) )  ;
  }

   ISINSIDEROI_API BOOL  G_PtInPolyRect(POINT *rgpts, int wnumpts, POINT ptTest, RECT *prbound)
 {
   RECT r ;

   // If a bounding rect has not been passed in, calculate it
   if (prbound) r = *prbound ;
   else{
      int   xmin, xmax, ymin, ymax ;
      POINT *ppt ;
      WORD  i ;

      xmin = ymin = INT_MAX ;
      xmax = ymax = -INT_MAX ;

      for (i=0, ppt = rgpts ; i < wnumpts ; i++, ppt++){
         if (ppt->x < xmin) xmin = ppt->x ;
         if (ppt->x > xmax) xmax = ppt->x ;
         if (ppt->y < ymin) ymin = ppt->y ;
         if (ppt->y > ymax) ymax = ppt->y ;
      }
      SetRect(&r, xmin, ymin, xmax, ymax) ;
   }
   return (PtInRect(&r,ptTest)) ;
 }


 /*************************************************************************
   * FUNCTION:   G_PtInPolygon
   *
   * PURPOSE
   * This routine determines if the point passed is in the polygon. It uses
   * the classical polygon hit-testing algorithm: a horizontal ray starting
   * at the point is extended infinitely rightwards and the number of
   * polygon edges that intersect the ray are counted. If the number is odd,
   * the point is inside the polygon.
   *
   * RETURN VALUE
   * (BOOL) TRUE if the point is inside the polygon, FALSE if not.
 *************************************************************************/

  ISINSIDEROI_API BOOL G_PtInPolygon(POINT *ppt, int wnumpts, POINT *ptTest, RECT *prbound)
  {
      int   count = 0, i, j = 0;
      POINT  ltp1, ltp2;

      if (!G_PtInPolyRect(ppt, wnumpts, (*ptTest), prbound)) return FALSE ;

      ltp1 = ltp2 = *ptTest;
      ltp2.x = (*prbound).right + 2;

      for ( i = 1; i <= wnumpts; i++) {
          if ( Intersect( *ptTest, *ptTest, ppt[i], ppt[i-1]) ) return TRUE; //On border or point.
          if ( !Intersect(ppt[i], ppt[i], ltp1,ltp2) ) {
              if ((Intersect(ppt[i],ppt[j],ltp1,ltp2))||((i != (j+1))&&((CCW(ltp1,ltp2,ppt[j])*CCW(ltp1,ltp2,ppt[i]))<1))) count++;
              j = i;
          }
      }
      if ( (j != wnumpts ) && (CCW(ltp1, ltp2, ppt[j]) * CCW(ltp1, ltp2, ppt[1])) == 1) count--;

      return (count&1);
   }

/*************************************************************************
   * FUNCTION:   G_PtInPolyRect
   *
   * PURPOSE
   * This routine determines if a point is within the smallest rectangle
   * that encloses a polygon.
   *
   * RETURN VALUE
   * (BOOL) TRUE or FALSE depending on whether the point is in the rect or
   * not.
 *************************************************************************/


