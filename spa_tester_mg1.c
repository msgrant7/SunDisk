// SPA Tester 'MG1' with Hampton Lat/Lon, Date, Time
// BEGAN:  Nov 2013 (during a disappointing, tough season)
// LATEST: 29 Dec 14
// Location Note:  http://www.findlatitudeandlongitude.com/
// Time Note: Standard time = UTC/GMT -5 hours
//            DST =  UTC/GMT -4 hours
//            (http://www.timeanddate.com/worldclock/)


/////////////////////////////////////////////
//          SPA TESTER for SPA.C           //
//                                         //
//      Solar Position Algorithm (SPA)     //
//                   for                   //
//        Solar Radiation Application      //
//                                         //
//             August 12, 2004             //
//                                         //
//   Filename: SPA_TESTER.C                //
//                                         //
//   Afshin Michael Andreas                //
//   afshin_andreas@nrel.gov (303)384-6383 //
//                                         //
//   Measurement & Instrumentation Team    //
//   Solar Radiation Research Laboratory   //
//   National Renewable Energy Laboratory  //
//   1617 Cole Blvd, Golden, CO 80401      //
/////////////////////////////////////////////

/////////////////////////////////////////////
// This sample program shows how to use    //
//    the SPA.C code.                      //
/////////////////////////////////////////////

#include <stdio.h>
#include "spa.h"  //include the SPA header file

int main (int argc, char *argv[])
{
    spa_data spa;  //declare the SPA structure
    int result;
    float min, sec;

    //enter required input values into SPA structure

    spa.year          = 2014;
    spa.month         = 12;
    spa.day           = 29;
    spa.hour          = 15;
    spa.minute        = 12;
    spa.second        = 30;
    spa.timezone      = -5.0;         // Hampton/East Coast
    spa.delta_ut1     = -0.45649;     // DUT1 = (UT1-UTC), from Navy IERS BULLETIN-A:
	                                  // http://maia.usno.navy.mil/ser7/ser7.dat
	//
    // Original delta_t = 67;  (see spa.h and http://maio.usno....)
    // spa.h gives delta_t = 32.184 + (TAI-UTC) - DUT1
    // Website maio.usno... gives: (TAI-UTC) = 35.000 sec
    //                             DUT1 = (UT1-UTC)) (see table on webpage
    //                      For 2013 11 25, UT1-UTC = -0.05344 (sec)
    //
    spa.delta_t       = 32.184 + 35.000 - (-0.05344);
    spa.longitude     = -76.385794;
    spa.latitude      = 37.098849;
    spa.elevation     = 1830.14;
    
    // Pressure (a heavy topic, in terms of units)
    //  1 mmHg (mercury) = 133.322387415 pascals (pa)
    //  1 Bar = 100,000 pascals  -> 1 millibar = 100 pascals
    //  Virginia pressure:  
    //  http://www.usairnet.com/weather/maps/current/virginia/barometric-pressure/
    //  spa.pressure is given in MILLIBARS = (mmHG * 133.32 Pa) / 100 Pa
    //  (original) spa.pressure      = 820;
    spa.pressure = (30.57 * 133.322387415) / 100;
    
    // VA temps
    // http://www.weather.com/weather/wxclimatology/monthly/graph/23669
    spa.temperature   = 13.89;    // deg. C  vs. 57 deg. F
    spa.slope         = 0.0;      // (flat)
    spa.azm_rotation  = 0.0;      // (flat)
    spa.atmos_refract = 0.5667;
    spa.function      = SPA_ALL;


    // Display spa.pressure to make sure it is in reasonable range:
    printf("\nAtmospheric press (mBars) is %f\n", spa.pressure);
    
    
    //call the SPA calculate function and pass the SPA structure

    result = spa_calculate(&spa);

    if (result == 0)  //check for SPA errors
    {
        //display the results inside the SPA structure

        printf("Julian Day:    %.6f\n",spa.jd);
        printf("L:             %.6e degrees\n",spa.l);
        printf("B:             %.6e degrees\n",spa.b);
        printf("R:             %.6f AU\n",spa.r);
        printf("H:             %.6f degrees\n",spa.h);
        printf("Delta Psi:     %.6e degrees\n",spa.del_psi);
        printf("Delta Epsilon: %.6e degrees\n",spa.del_epsilon);
        printf("Epsilon:       %.6f degrees\n",spa.epsilon);
        printf("Zenith:        %.6f degrees\n",spa.zenith);
        printf("Azimuth:       %.6f degrees\n",spa.azimuth);
        printf("Incidence:     %.6f degrees\n",spa.incidence);

        min = 60.0*(spa.sunrise - (int)(spa.sunrise));
        sec = 60.0*(min - (int)min);
        printf("Sunrise:       %02d:%02d:%02d Local Time\n", (int)(spa.sunrise), (int)min, (int)sec);

        min = 60.0*(spa.sunset - (int)(spa.sunset));
        sec = 60.0*(min - (int)min);
        printf("Sunset:        %02d:%02d:%02d Local Time\n", (int)(spa.sunset), (int)min, (int)sec);

    } else printf("SPA Error Code: %d\n", result);

    return 0;
}

/////////////////////////////////////////////
// The output of this program should be:
//
//Julian Day:    2452930.312847
//L:             2.401826e+01 degrees
//B:             -1.011219e-04 degrees
//R:             0.996542 AU
//H:             11.105902 degrees
//Delta Psi:     -3.998404e-03 degrees
//Delta Epsilon: 1.666568e-03 degrees
//Epsilon:       23.440465 degrees
//Zenith:        50.111622 degrees
//Azimuth:       194.340241 degrees
//Incidence:     25.187000 degrees
//Sunrise:       06:12:43 Local Time
//Sunset:        17:20:19 Local Time
//
/////////////////////////////////////////////

