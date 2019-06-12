/****************************************************************************/
/*    Math3D Library. Performs 3D Vector and matrix calculations.           */
/*    Simle 3D graphics objects.					    */
/*    Copyright (C), 1991-2012,  Andrei Volkov                              */
/*                                                                          */
/*    This program is free software: you can redistribute it and/or modify  */
/*    it under the terms of the GNU General Public License as published by  */
/*    the Free Software Foundation, either version 3 of the License, or     */
/*    (at your option) any later version.                                   */
/*                                                                          */
/*    This program is distributed in the hope that it will be useful,       */
/*    but WITHOUT ANY WARRANTY; without even the implied warranty of        */
/*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         */
/*    GNU General Public License for more details.                          */
/*                                                                          */
/*    You should have received a copy of the GNU General Public License     */
/*    along with this program.  If not, see <http://www.gnu.org/licenses/>. */
/****************************************************************************/
/*   IMAGES header                                                          */
/*   A. Volkov, 1991                                                        */
/****************************************************************************/

#ifndef __O_IMAGES
#define __O_IMAGES

#include <stddef.h>
#include "videodev.h"
#include "analytic.h"

class video_system;

typedef int point_proection[2];

class part_image
{
  public:
    part_image* next;
    REAL_TYPE distance;//, fill;
    virtual ~part_image() {}
    virtual void draw(video_system* v_s) {v_s=v_s;} //Abstract
};

//01.23.2016
//class points_image; //forward
class _point
{
  //friend class points_image;
  //protected:
  //  int color,x,y;
  public:
    int color,x,y;
    _point() {}
    _point(int c, int _x, int _y)
    {
      color=c; x=_x; y=_y;
    }
};

class v_point
{
  //friend class points_image;
  //protected:
  //  int color,x,y;
  public:
    int color,x,y;
    REAL_TYPE value;
    v_point() {}
    v_point(int c, int _x, int _y, REAL_TYPE v)
    {
      color=c; x=_x; y=_y; value=v;
    }
};

//01.23.2016 - added _point inheritance
class point_image: public part_image, public _point
{
 public:
  //int color,x,y; //commented 01.23.2016
  point_image(int c, int _x, int _y,
             part_image* _next,
             REAL_TYPE d) : _point(c, _x,_y)
  {
   //color=c; x=_x; y=_y;
   next=_next;
   distance=d;
  }
  virtual void draw(video_system* v_s);
};

//01.23.2016 - added
class points_image: public part_image
{
  protected:
    v_point* points;
    int count;
    int color;
    //virtual void calculate() {}
  public:
    points_image(int c, int cnt, part_image* _next, REAL_TYPE d) {
      color = c;
      count = cnt;
      points = new v_point[count];
      next=_next;
      distance=d;
    }
    v_point& operator [](int i) {return points[i];}
    virtual ~points_image() { delete points; }
    virtual void draw(video_system* v_s);
};

//12.27.2015
class lock_image: public part_image
{
 public:
  int color,x,y,r;
  lock_image(int c, int _x, int _y, int _r,
             part_image* _next,
             REAL_TYPE d)
  {
   color=c; x=_x; y=_y; next=_next;r=_r;
   distance=d;
  }
  virtual void draw(video_system* v_s);
};

//12.08.2015
class circle_image: public part_image
{
 public:
  int color,x,y,r;
  circle_image(int c, int _x, int _y, int _r,
             part_image* _next,
             REAL_TYPE d)
  {
   color=c; x=_x; y=_y; next=_next;r=_r;
   distance=d;
  }
  virtual void draw(video_system* v_s);
};

class poly_image: public part_image
{
 public:
  int color, num_points;
  //int* poly_points;
  int* poly_points;
  //poly_image* next;
  REAL_TYPE /*distance,*/ value;

  poly_image(int c, int n_p, int* p_p,
             part_image* _next,
         REAL_TYPE d, REAL_TYPE v)
  {
   color=c; num_points=n_p; poly_points=p_p; next=_next;
   distance=d; value=v;
  }
  virtual ~poly_image() {delete poly_points;}
  virtual void draw(video_system* v_s);
};

class image: public part_image
{
 //poly_image* image_elements;
  part_image* image_elements;
 public:
  image() {image_elements = NULL; next=NULL;}
  virtual ~image();

  virtual void draw(video_system* v_s);
  void clear();
  //image& operator +=(poly_image* p_i);
  image& operator +=(part_image* p_i);
  image& operator +=(image* p_i); //uncommented 1.2.2015
};

#endif
