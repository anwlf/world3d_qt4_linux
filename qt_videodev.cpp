/***********************************************************/
/*   Video device for QT, implementation                   */
/*   A. Volkov 2010                                        */
/***********************************************************/

#include "qt_videodev.h"

/***********************************************************/
/* Drav polygon method implementation                      */
/***********************************************************/
void qt_video_system::draw_poly(int num_points,int *poly_points,int color,
                                 REAL_TYPE value)
{
    // Allocates temporary array for points
    //QPoint* points = new QPoint[num_points]; //commented 12.31.2015
    QPoint points[num_points]; //12.31.2015
    //
    int p=0; // 12.03.2015 - optimize drawing speed
    for (int i=0; i<num_points; i++) {
        points[p].setX(poly_points[i*2]);
        points[p].setY(poly_points[(i*2)+1]);
        //12.03.2015 - optimize drawing speed
        for (int j=0; j<p; j++) {
            if ((points[p].x() == points[j].x()) && (points[p].y() == points[j].y())) {
                p--;
                break;
            }
        }
        p++;
    }
    QColor c(color);
    //Calculates color RGB components intensivity
    if (value<0.0) value=0.0;  //test 12.06.2015
    qreal red=c.redF()*value,
          green=c.greenF()*value,
          blue=c.blueF()*value;
    // Creates color drom RGB
    //test 12.06.2015
    /*
    if (red>1.0) red=1.0;
    if (green>1.0) green=1.0;
    if (blue>1.0) blue=1.0;
    if (red<0.0) red=0.0;
    if (green<0.0) green=0.0;
    if (blue<0.0) blue=0.0;
    */
    c=QColor::fromRgbF(red,green,blue,1);
    // Sets pen and brush
    painter.setPen(c);
    // 12.02.2015 - drawPoint for far_objects
    // 12.03.2015 - optimize drawing speed - p instead num_points
    if (/*num_points*/p > 1) {
        painter.setBrush (QBrush(c));
        // Draws polygon
        painter.drawPolygon(points, /*num_points*/p);
    } else {
        painter.drawPoint(points[0]);
    }
    // Releases memory
    //delete points; //commented 12.31.2015
}

void qt_video_system::draw_point(int x,int y,int color)
{
    QColor c(color);
    painter.setPen(c);
    painter.drawPoint(x,y);
}

void qt_video_system::draw_point(int x,int y,int color, REAL_TYPE value) //12.08.2015, 01.26.2016
{
    QColor c(color);
    if (value<0.0) value=0.0;  //01.26.2016
    if (value<1.0) {
      qreal red=c.redF()*value,
      green=c.greenF()*value,
      blue=c.blueF()*value;
      c=QColor::fromRgbF(red,green,blue,1);
    }
    painter.setPen(c);
    painter.drawPoint(x,y);
}

void qt_video_system::draw_circle(int x,int y,int r,int color, bool fill) //12.08.2015
{
    QColor c(color);
    painter.setPen(c);
    if (fill) {
      painter.setBrush(QBrush(c));
    } else {
      painter.setBrush(QBrush(Qt::transparent));
    }
    painter.drawEllipse(x-r,y-r,r*2,r*2);
}

