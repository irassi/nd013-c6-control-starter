/**********************************************
 * Self-Driving Car Nano-degree - Udacity
 *  Created on: December 11, 2020
 *      Author: Mathilde Badoual
 **********************************************/

#include "pid_controller.h"
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kpi, double Kii, double Kdi, double output_lim_maxi, double output_lim_mini) {
   /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   **/
  Kp = Kpi;
  Ki = Kii;
  Kd = Kdi;
  output_lim_max = output_lim_maxi;
  output_lim_min = output_lim_mini;
  sum_cte = 0.0;
  diff_cte = 0,0;
  prev_cte = 0.0;
  delta_time = 1;

}


void PID::UpdateError(double cte) {
   /**
   * TODO: Update PID errors based on cte.
   **/
  diff_cte = cte - prev_cte;
  sum_cte += cte;
  prev_cte = cte;
}

double PID::TotalError() {
   /**
   * TODO: Calculate and return the total error
    * The code should return a value in the interval [output_lim_mini, output_lim_maxi]
   */

//   Check for 0 values for delta_time
    double d_err = 0;
    if (delta_time > 0) {
      double d_err = Kd * diff_cte / delta_time;
      std::cout << "dt over 0, calculate d_err: "  << d_err << endl;

    } else {
      // If dt is 0, set d_err to 0 too
      double d_err = 0;
      std::cout << "dt 0, calculate d_err: "  << d_err << endl;

    }
    // The course material gave the formula as "-tau_p * cte - tau_d * diff_cte - tau_i * sum_cte" 
    // This gives negative values for throttle so I will remove the negatives
    double control = Kp * prev_cte + d_err + Ki * sum_cte;

   //Super debug stack
    std::cout << '\n';
    std::cout << "Kp: "  << Kp << endl
              << "prev_cte: " << prev_cte << endl
              << "Kd: "  << Kd << endl
              << "diff_cte: "  << diff_cte << endl
              << "delta_time: "  << delta_time << endl
              << "Ki: "  << Ki << endl
              << "sum_cte: "  << sum_cte << endl
              << "Control: "  << control << endl;
    std::cout << '\n';


    if (control > output_lim_max) {
      control = output_lim_max;
    }     

    if (control < output_lim_min) {
      control = output_lim_min;
    }


    return control;
}

double PID::UpdateDeltaTime(double new_delta_time) {
   /**
   * TODO: Update the delta time with new value
   */
  delta_time = new_delta_time;
}