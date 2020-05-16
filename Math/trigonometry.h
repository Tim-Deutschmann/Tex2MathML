#ifndef _trigonometry_h
#define _trigonometry_h

#include <math.h>

inline double Rad(const double& angle_degree){return (M_PI*angle_degree)/180.0;}
inline double Degree(const double& angle_rad){return (180.0*angle_rad)/M_PI;}

inline double correctMu(const double& mu){return mu<-1.0?-1.0:(mu>1.0?1.0:mu);}

#endif //_trigonometry_h

